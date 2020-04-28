var PROTO_PATH = 'marks.proto';

var fs = require('fs');
var _ = require('lodash');
var grpc = require('grpc');
var protoLoader = require('@grpc/proto-loader');
var packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });

var marks_proto = grpc.loadPackageDefinition(packageDefinition).marks;

let rawdata = fs.readFileSync('marks.json');
let marks_data = JSON.parse(rawdata);

/**
 * Implements the GetMarks Service
 */
function getMarks(call) {
    var start_time = process.hrtime();
    console.log('GetMarks Called by: ' + call.metadata._internal_repr['user-agent']);
    call.on('data', function (student) {
        var data = {
            student_name: student.name,
            marks: marks_data[student.name]
        }
        call.write(data);
    });
    call.on('end', function () {
        console.log({ elapsed_time: process.hrtime(start_time) });
        call.end();
    });
}

/**
 * Starts an RPC server that receives requests for the Greeter service at the
 * sample server port
 */
function main() {
    var server = new grpc.Server();
    server.addService(marks_proto.MarksPortal.service, { getMarks: getMarks });
    server.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
    console.log("Server Started on 0.0.0.0:50051");
    server.start();
}

main();