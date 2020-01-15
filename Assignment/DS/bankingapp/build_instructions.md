## install mongo-c driver by
```
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.15.3/mongo-c-driver-1.15.3.tar.gz
tar xvf mongo-c-driver-1.15.3.tar.gz
cd mongo-c-driver-1.15.3/
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
make -j8 && sudo make install
```

## install mongo-cxx driver by
```
curl -OL https://github.com/mongodb/mongo-cxx-driver/archive/r3.4.0.tar.gz
tar xvf r3.4.0.tar.gz
cd mongo-cxx-driver-r3.4.0
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local
sudo make EP_mnmlstc_core
make && sudo make install
```

## configuring mongodb
```
mkdir /data/db
sudo chmod -R go+w /data/db
sudo service mongogb restart
sudo apt install mongodb mongodb-server
```

For building the mongo test use this ``c++ --std=c++11 test.cpp $(pkg-config --cflags --libs libmongocxx) -Wl,-rpath,/usr/local/lib``

> all the best 😂😂
