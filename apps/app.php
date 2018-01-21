<?php
//copy this file in apache web sever folder /var/www/html next to marinecoin.php in the same folder
/* .marinecoin/marinecoin.conf file should have the below settings
rpcuser=testuser
rpcpassword=testpassword
server=1
listen=1
testnet=1
addnode=188.226.192.77
rpcallowip=127.0.0.1
rpcport=54595
---------------------------------------------------------*/

require_once('marinecoin.php');
$marinecoin = new Marinecoin('testuser','testpassword');

echo $marinecoin->getblockcount();
echo "<br>";
echo $marinecoin->getbalance();
?>
