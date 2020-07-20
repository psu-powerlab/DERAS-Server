from ubuntu:latest
arg DEBIAN_FRONTEND=noninteractive
run apt-get update && apt-get dist-upgrade -y && apt-get -qq install build-essential -y && \
	# dist upgrade so we can locate the needed packages
	apt-get install libxerces-c-dev vim wget locate cmake libssl-dev -y && \
	apt-get install libmysqlcppconn-dev libboost-all-dev git mysql-server -y
	#git clone https://github.com/psu-powerlab/DERAS-Server.git
copy . /DERAS
cmd ["/bin/bash"]
