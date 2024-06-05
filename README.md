# FinalCPX-PopLock
Demo Repo for ENGR 103.

## Description
It is a timing game. One random spot/LED will be chosen on the board and a different light will be spinning around. The goal is to press a button as soon as the spinning light is on the random LED and that counts as one point. As soon as you correctly time the press, it will play a ping type of sound and the spinning light will now spin the opposite direction. As you continue to score higher, the spinning will also get faster. There will be multiple difficulty levels that adjust how long you will go for. For the default difficulty, the goal is to get fifty points and in doing so, the board will play an animation and happy music cue. If you mess up and incorrectly time the button press to the LED, then it will play a mean/sad tune and a red animation. I will be using the serial print to show what your score is as well as your highscore.

## Difficulty Levels
Left button will determine the difficulty level. There will be three levels, 1, 2, 3.

Level 1: Make it up to 50 points. Spinning speed will start off slow and be relatively fast by the end.

Level 2: Make it up to 75 points. Speed will be the same as level one but due to the longer length it will be faster at the end.

Level 3: Make it up to 100 points. Speed will be the same as level one but due to the longer length it will be faster at the end. (Goal is to make it feel impossible to finish but still possible if you waste an insane amount of time trying).

## Input/Outputs
Input/Outputs:
There will be three inputs and three outputs.

Input 1 (Right Button): This will be the button to set the difficulty level going from 1 to 3 and resetting to 1 after 3. It will use an attach interrupt on 4 and a for loop will determine what lights are on.

Input 2 (Left Button): This will be the button you use to time your presses right on the LED.

Output 1 (LEDs): There will be one bright green LED sitting on a random spot. The other LED will be a different color spinning around the LEDs. It will react to the right button press depending if you timed it right or not. If you miss the timing of the button press it will play an angry/red animation at you. If you make it to the end depending on the difficulty level, it will play a happy/green animation at you. 

Output 2 (Sound): Each time you correctly time the button press, a ping noise will play. If you mess up the timing it will play a distraught/sad/angry tone at you. If you make it to the end depending on the difficulty level, it will play a happy tone at you. 

Output 3 (SerialPrint): This will display your score count as well as what difficulty level you're at. If you miss the timing it will display some text saying you failed. If you make it to the end it will display some text saying congratulations.
