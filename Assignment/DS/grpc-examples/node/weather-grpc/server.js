var PROTO_PATH = 'weather.proto';

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

var weather_proto = grpc.loadPackageDefinition(packageDefinition).weather;

let rawdata = fs.readFileSync('city_temps.json');
let city_data = JSON.parse(rawdata);

/**
 * Implements the GetWeather Service
 */
function getWeather(call) {
    var cityName = call.request.city_name;
    console.log('GetWeather Called by: ' + call.metadata._internal_repr['user-agent']);

    _.each(city_data, function (data) {
        data_res = {
            timestamp: data.timestamp,
            city: cityName,
            temp: data.temp,
            weather_status: "cloudy",
        }
        call.write(data_res);
    });

    call.end();
}

/**
 * Starts an RPC server that receives requests for the Greeter service at the
 * sample server port
 */
function main() {
    var server = new grpc.Server();
    server.addService(weather_proto.Weather.service, { getWeather: getWeather });
    server.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
    console.log("Server Started on 0.0.0.0:50051");
    server.start();
}

main();