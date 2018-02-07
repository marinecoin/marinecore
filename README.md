# Marinecore

Marinecoin - MTC
http://marinecoin.info

### Prerequisites

Recommended and tested installation platform Ubuntu 14.04 Server or Desktop, Ubuntu 16.04 Server or Desktop. Installation may require additional steps on other flavors of Unix based operating systems.  On local machines during Ubuntu installation select location "United States"  and language as "English" keyboard layout does not matter, if you select other countries dependency installation may not have access to some of the required repositories.

Clean install your preferred Ubuntu OS on a VPS or a local machine with at least 512MB Ram.
Tutorial on setting up ubuntu can be found [here.](https://www.wikihow.com/Install-Ubuntu-Linux)

After you are up and running on Ubuntu, run the Terminal application if you are on the Desktop version to access the command line area.

Make sure your locales are set permanently, to do that you must have root access to the Ubuntu terminal.

Setting Locale switch set the password for root, switch to root user with the following commands

		sudo passwd root
		
Enter and confirm the root password on prompt

		su root

Enter the following four lines one by one as root

		export LC_ALL="en_US.UTF-8"
		export LANGUAGE="en_US.UTF-8"
		echo 'LANGUAGE="en_US.UTF-8"' >> /etc/default/locale
		echo 'LC_ALL="en_US.UTF-8"' >> /etc/default/locale

That's it for locale now switch to the other user or stay as root as per your requirements to install Marinecore dependencies.

Switch to username used during Ubuntu installation, or remain as root; this is optional depending on your project requirements.

		su username

If you have limited hardware RAM 512 MB to 1024 MB, you must enable the swap file to create extra virtual memory on your hard drive to successfully compile Marinecore from source. You may skip this step if you have at least 2GB of memory.

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

Now that all the dependencies are installed, we can start building

		cd
		sudo git clone https://github.com/marinecoin/marinecore.git
		cd marinecore/src
		sudo make -f makefile.unix USE_UPNP=-
		strip marinecoind
		sudo cp marinecoind /usr/bin
		cd

We have installed Marinecore for Marinecoin, now we will start the wallet once so that it can create the necessary data directories. Just type:

		marinecoind &

This will give us a warning message that the marinecoin.conf configuration file needs to be set in the .marinecoin hidden directory, type: (notice .marinecoin folder starts with a "dot" . )

		cd .marinecoin
		sudo nano marinecoin.conf

In the text editor that opened on the console copy & paste the following two lines into the file

		rpcuser=any_user_name_you_want
		rpcpassword=any_password_you_want

on your keyboard
press Ctrl+O to save
press ENTER to confirm
press Ctrl+X to exit

We have set the config file, now type: ./marinecoind & again to start the core wallet.

		marinecoind &

You should see a process id appear indicating the Marinecore has started successfully. To get the general status of the Daemon process type:

		marinecoind getinfo

You should now see the blockchain is in the process of synchronization with other peers. Check using above "./marinecoind getinfo" to follow the progress until the entire Marinecoin blockchain download is complete, confirm the last block count from https://explorer.marinecoin.info. Once the Marinecore synchronization is complete, we can start using it in our tutorial projects to develop web apps and payment interactions amongst automated machines, robots and exchanges.

Check your MTC balance with the following command

		marinecoind getbalance
		
List all the available commands

		marinecoind help
		
List all the account names

		marinecoind listaccounts
		
You should see this output for listaccounts

		{
		""
		}
The default account is "" - now we can get the MTC address of the default account by getaccountaddress command, just type:

        marinecoind getaccountaddress ""
        
The output will give your Marinecoin default receiving address. Let's create a new account now.

        marinecoind getnewaddress your_new_account_name
        
List all the account names

        marinecoind listaccounts
        marinecoind getaccountaddress your_new_account_name

Now that you created this MTC address you can receive Marinecoins to this address also. Send MTC to your new address from the exchange or your Mac or Windows GUI wallet. To check its balance just type:

        marinecoind getbalance your_new_account_name 0
        
You should now see the sent amount on your new account. Above notice, we put a 0 at the end, that represents the number of confirmations on the network after receiving MTC. If we had entered 1 and no new block had confirmed the transaction since it had been sent, the balance would have still shown zero.

What we have done so far was passing RPC commands to the Marinecore and getting status of the wallet database and the blockchain status using the console. We can use these commands in our projects and have our custom apps, databases, or websites access the same wallet information using an RPC connection and do many more cool things with it.

But first, since we are under development mode it would be a better option to switch Marinecore to the Sandbox mode which will use the Marinecoin testnet network so that we can access free Sandbox MTC which has no value. This way if we make a mistake erase or lose data during development we won't lose any real MTC.

First stop Marinecore

		marinecoind stop
		
Now we will edit the config file so that next time when we start Marinecore it will start on Sandbox mode.

		cd
		cd .marinecoin
		sudo nano marinecoin.conf
		
The text editor will open the file we created earlier to enter our rpcuser and rpcpassword, edit the conf file to look like below.
		
		rpcuser=testuser
		rpcpassword=testpassword
		server=1
		listen=1
		testnet=1
		addnode=188.226.192.77
		rpcallowip=127.0.0.1
		rpcport=54595
		
on your keyboard
press Ctrl+O to save
press ENTER to confirm
press Ctrl+X to exit

Type the following command to start Marinecore again. This time on Sandbox mode.

		marinecoind &

Now you can setup a web server to create your first web app, install LAMP server, place the two PHP files in marinecore/app to /var/www/html folder if you are on apache

        cd
        sudo cp marinecore/app/marinecoin.php /var/www/html/marinecoin.php
        sudo cp marinecore/app/app.php /var/www/html/app.php
        sudo apt-get install php-curl
        sudo service apache2 restart
        
On your web browser navigate to the app.php file http://your_server_ip_address/app.php
You should now see the current Marinecoin network block count above and the current Sandbox wallet balance below.

If we check to see our account addresses, we will notice this time their first letter now starts with the letter J or K instead of m or n on the real MTC network.

We can either get free Sandbox MTC from the Marinecoin website's testnet faucet or by mining them with our CPU with a single command.

        marinecoind setgenerate true 16
        
After this command, your computer will start mining some Sandbox coins, leave it on for a few hours and check your balance. You can also mine the real MTC network this way.

So far with few short commands, we have established a connection to Marinecore with a simple web application. Other programming languages can also be used to connect to the Core Marinecoin wallet as similar to the PHP example shown. From there database storage and other GUI representations of the wallet information can be achieved.

To send funds to another Marinecoin address from RPC console, change the PHP sample code accordingly to communicate from a web app, the below command will send 1200.125 MTC to the below MTC address if the wallet has enough balance

        marinecoind sendtoaddress moQFE67TrB6kFZsA3XuWKTyeHqcDc8Hvfw 1200.125
        
By now you should have a basic understanding of the Marinecore blockchain and its capabilities to send and receive payments and the possibilities that it represents.
