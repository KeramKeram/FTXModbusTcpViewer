# FTXModbusTcpViewer
Very easy viewer for modbus. <b> PROGRAM WAS TESTED USING PYMODUS. NO WARRANTY IS WORK WITH OTHER SOFTWARE</b>.
Program is still in active development, but is currently is able to read register from modbus server and show them on screen.

# Build
Build tested only on Linux.
run build script:

```
./build.sh
```

After build go to bin folder. If build was successful you can run software in that way:

```
./FTXModbusTcpViewer
```

# Configuration
In file configuration.json you can find configuration of the program(for current version is limited).
This file is copied to bin folder by build script:
In configuration(who is json file) we can find three main parts:
- register-interval
  This part is saying where is beginning/end address of modbus register. For example coils-star: 0 is saying that 
  we're starting read from coils from address 0, coils-end: 20 says that we stop reading on address 20. That means 
  we read 21 addresses.
- network-configuration.
  Simply network configuration for modbus server what we want to connect.
- view-configuration.
  We can manipulate view output. Currently, we can only change number of displayed rows.

All changes in configuration required restart of program.
  
