<?php

function getRandomCharacter() {
    // Define your list of characters
    $characters = array('A', 'B', 'C'); 
    // Get a random index from the characters array
    $randomIndex = array_rand($characters);
    // Return the character at the random index
    return $characters[$randomIndex];
}

function getRandomAction() {
    // Define your list of actions
    $action = array('pick', 'place'); 
    // Get a random index from the actions array
    $randomIndex = array_rand($action);
    // Return the character at the random index
    return $action[$randomIndex];
}

function getRandomStatus() {
    // Define your list of status
    $status = array('full', 'empty'); 
    // Get a random index from the status array
    $randomIndex = array_rand($status);
    // Return the status at the random index
    return $status[$randomIndex];
}

$arr['row'] = getRandomCharacter(); //a random character from the above list
$arr['col'] = random_int(0, 4); //a random value between 1 and 5
$arr['action'] = getRandomAction(); //a random action
$arr['status'] = getRandomStatus(); //a random value

$json=json_encode($arr); //convert the array in json format 
echo"$json"; //send the json response

/* Save the response and client data to a file locally on server*/
$t=time();
$date_time= date('H:i:s', $t);

$ip=$_SERVER["REMOTE_ADDR"]; //IP address of client requesting the data

$str=" Server Time: $date_time \n\n Client IP: $ip \n\n Data sent: $json";
file_put_contents("response.txt", $str); //save the data in a text file

?>
