[MAC OS X] Installing additional software:


Open the Terminal application and follow the instructions below, step by step (not as a root user).

/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)”
brew update
brew upgrade
brew install gcc
brew install qt
brew install autoconf automake libtool miniupnpc protobuf openssl berkeley-db4 boost pkg-config zmq libevent
brew install libqrencode
brew install librsvg
brew install python3



[FEREN OS, UBUNTU 18.04, 16.04] Installing additional software:
Open the Terminal application and follow the instructions below, step by step.

sudo apt-get update
sudo apt-get install software-properties-common python-software-properties
sudo apt-add-repository ppa:bitcoin/bitcoin
sudo apt-get update

sudo apt-get install autoconf libzmq3-dev build-essential libtool autoconf libssl-dev libboost-dev libboost-chrono-dev libboost-filesystem-dev libboost-program-options-dev libboost-system-dev libboost-test-dev libboost-thread-dev sudo automake git wget curl bsdmainutils libminiupnpc-dev libgmp3-dev ufw pkg-config libevent-dev libdb5.3++ unzip libzmq5

sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev

[ALL] Network Blockchain:
RPC Port : 5655
P2P Port : 5656
Explorer: http://192.99.68.144/



[ALL] Save additional nodes in the proelio.conf file:
addnode=51.75.122.68
addnode=35.242.179.166
addnode=35.228.11.21
addnode=35.228.115.74
addnode=35.228.46.173
addnode=35.196.242.178
addnode=35.228.147.25
addnode=35.228.236.146
addnode=217.182.73.189
addnode=35.228.176.70
addnode=51.38.131.112
addnode=51.68.196.27
addnode=35.242.173.80
addnode=51.75.122.66
addnode=35.234.151.73
addnode=35.234.133.207
