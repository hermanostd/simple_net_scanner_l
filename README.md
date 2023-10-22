# simple_net_scanner_l
Simple, lightweight tool to show devices connected to your local network. (Linux)

Manual:

1. Visibility:
   -0 (shows only live hosts and their respectable ip address)
   -1 (shows all of the scanning resoults including dead addresses)
   -2 (shows the bash commands used in the bash !(WIP))

2. Timeout and port selection
   -you are given an option to select a ping timeout in milisecons (note: it is recommended to keep it above 50 to     ensure all of the devices get recognised)
   -you can also select a nuber of ports to be scanned, it starts at .1 and checks until the given number

ToDo list:
    -multithreading (why not :D)
    -manual port range settings
    -manual gate selection
    -optimising the structure and improoving the modularity
    -better debuging system
    -improoved precision (multiple ping runs)

    Will see if its viable to implement on windows.
