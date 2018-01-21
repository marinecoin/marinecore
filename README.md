# Marinecore

Marinecoin - MTC
http://marinecoin.info

### Prerequisites

Recommended and tested installation platform Ubuntu 14.04 Server or Desktop, Ubuntu 16.04 Server or Desktop. Installation may require additional steps on other flavors of Unix based operating systems.  On local machines during Ubuntu installation select location "United States"  and language as "English" keyboard layout does not matter, if you select other countries dependency installation may not have access to some of the required repositories.

Clean install your preferred Ubuntu OS on a VPS or a local machine with at least 512MB Ram.

Make sure your locales are set permanently, to do that you must have root access to the Ubuntu terminal.

Setting Locale switch set the password for root, switch to root user with the following commands

sudo passwd root
"enter and confirm the root password"
su root

copy paste the following four lines as root

export LC_ALL="en_US.UTF-8"
export LANGUAGE="en_US.UTF-8"
echo 'LANGUAGE="en_US.UTF-8"' >> /etc/default/locale
echo 'LC_ALL="en_US.UTF-8"' >> /etc/default/locale

"that's it for locale now switch to the other user or stay as root as per your requirements to install Marinecore dependencies."

"username used during Ubuntu installation, or remain as root; this is optional."

su username

İf you have limited hardware RAM 512 MB to 1024 MB, you must enable the swap file to create extra virtual memory on your hard drive to successfully compile Marinecore from source. You may skip this step if you have at least 2GB of memory.

sudo swapon -s
sudo fallocate -l 2G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
sudo sysctl vm.swappiness=10
sudo sysctl vm.vfs_cache_pressure=50
sudo cp /etc/fstab /etc/fstab.bak
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
echo 'vm.swappiness=10' >> /etc/sysctl.conf
echo 'vm.vfs_cache_pressure=50' >> /etc/sysctl.conf

Let's intall the dependencies with the following commands

sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install libssl-dev
sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install libdb4.8-dev
sudo apt-get install libdb4.8++-dev
 sudo apt-get install libboost-all-dev
sudo apt-get -y install git

Now that all the dependencies are install we can start building

cd
sudo git clone https://github.com/jarviscoin/marinecore.git
cd marinecore/src
make -f makefile.unix USE_UPNP=-
strip marinecoind
cp marinecoind /usr/bin
cd

We have installed Marinecore for Marinecoin, now we will start the wallet once so that it can create the necessary data directories. Just type:

./marinecoind &

This will give us a warning message that the marinecoin.conf configuration file needs to be set in the .marinecoin hidden directory, type: (notice .marinecoin folder starts with a "dot" . )

cd .marinecoin
sudo nano marinecoin.conf

In the text editor enter the following two lines

rpcuser=any_user_name_you_want
rpcpassword=any_password_you_want

press Ctrl+O to save
press ENTER to confirm
press Ctrl+X to exit

We have set the config file, now type: ./marinecoind & again to start the core wallet.

./marinecoind &

You should see a process id appear indicating the Marinecore has started successfully. To get the general status of the Daemon process type:

./marinecoind getinfo

You should now see the blockchain is in the process of synchronization with other peers. Check using above "./marinecoind getinfo" to follow the progress until the entire Marinecoin blockchain download is complete, confirm the last block count from https://explorer.marinecoin.info. Once the Marinecore synchronization is complete, we can start using it in our tutorial projects to develop web apps and payment interactions amongst automated machines, robots and exchanges.