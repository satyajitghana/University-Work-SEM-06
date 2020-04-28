var PROTO_PATH = 'marks.proto';

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

var student = ['satyajit', 'shubham', 'samhitha', 'shikhar', 'shobhan'];

var client = new marks_proto.MarksPortal('localhost:50051',
    grpc.credentials.createInsecure());

function runGetMarks(callback) {
    console.log('START STREAM');
    var call = client.getMarks();

    call.on('data', function (marks_data) {
        console.log(marks_data);
    });

    call.on('end', callback);

    _.each(student, function (std) {
        var my_student = { name: std };
        call.write(my_student);
    });

    call.end();
}

function main() {

    runGetMarks(function () {
        console.log("END OF STREAM");
    });
}

main();