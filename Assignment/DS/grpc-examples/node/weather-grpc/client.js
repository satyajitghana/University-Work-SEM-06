var PROTO_PATH = 'weather.proto';

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

var client = new weather_proto.Weather('localhost:50051',
    grpc.credentials.createInsecure());

function runGetWeather(callback) {
    console.log('STREAMING WEATHER DATA FOR Bangalore');

    var city = {
        city_name: "bangalore",
    }

    var call = client.getWeather(city);

    call.on('data', function (weather_data) {
        console.log(weather_data);
    });

    call.on('end', callback);
}

function main() {

    runGetWeather(function () {
        console.log("END OF STREAM");
    });
}

main();