<?php
  // необходимые HTTP-заголовки 
//  header("Access-Control-Allow-Origin: *");
  header("Content-Type: application/json; charset=UTF-8");
//  header("Access-Control-Allow-Methods: POST");

  $method = $_SERVER['REQUEST_METHOD'];
  $req = $_GET['req'];

  if ($method === 'POST') {
    $postData = file_get_contents('php://input');

    if (stripos($_SERVER["CONTENT_TYPE"], 'application/json') !== false) {
      $jsonData = json_decode($postData, true);
    }
  }

  if ($req === 'draw') {
    $drawState = 0;
    $drawCount = 0;

    if ($method === 'POST') {
      switch ($jsonData['cmd']) {
        case 'on':
          $drawState = 1;
          break;
        case 'off':
          $drawState = 0;
          break;
        case 'add':
          $drawState = 1;
          $drawCount = hexdec(substr($jsonData['val'], 0, 2));
          break;
        case 'del':
          $drawState = 1;
          $drawCount = 10 - intval($jsonData['val']);
          break;
        case 'clr':
          $drawState = 1;
          $drawCount = 0;
          break;
      }
    }

    echo json_encode(array(
      'state' => $drawState,
      'cnt' => $drawCount
    ));
  }
  else if ($req === 'test_led') {
    $drawState = 0;

    if ($method === 'POST') {
      switch ($jsonData['cmd']) {
        case 'O':
        case 'R':
        case 'G':
        case 'B':
        case 'L':
        case 'K':
          $drawState = 1;
          break;
      }
    }

    echo json_encode(array(
      'state' => $drawState
    ));
  }
  else if ($req === 'simple_effects') {
    $effect = '';

    if ($method === 'POST') {
      $effect = $jsonData['cmd'];
    }

    echo json_encode(array(
      'effect' => $effect
    ));
  }
?>
