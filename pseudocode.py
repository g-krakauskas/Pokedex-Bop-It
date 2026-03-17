//function to check for input completion within time; same for all commands
Bool waitForCompletion(input, timer)
{
startTime = currentTime();

while (currentTime() - startTime < timer)
    	{
if (readInput() == input)
        		{
            		return true;
       		 }
   	 }
    	return false;
}
// function def for catch 
Bool catch(timer)
{
	success = false;
Catch command audio;
If (waitForCompletion(dial, timer) == true)
{
Play successful catch audio;
	success = true;
}
return success;
}
//function def for attack
Bool attack()
{
	success = false;
attack command audio;
If (waitForCompletion(joystick, timer) == true)
{
Play successful attack audio
	success = true;
}
return success;
}
//function def for evolve
Bool evolve()
{
	success = false;
evolve command audio;
If (waitForCompletion(shake, timer) == true)
{
Play successful evolve audio
	success = true;
}
Return success;
}
main()
{	
	Score = 0;
	Level = 1;
	Timer = 5;

	//Array holding each command function call
	commands = [catch, attack, evolve]
	//Checks top button state for on/off status
	If (on == true)	
	{
		//Checks state of reset button
		If (reset == true)
{
	Score = 0;
			Level = 1;
Start game;
	While (Score < 100)
{
	//makes a random choice of the commands
cmd = random.choice(commands)
success = cmd(timer);

If (success == true)
{
					Score++;

If (Score % 10 == 1)
{
//timer duration decreases every 
	timer = timer - 0.5;
Level++;
}
}
Else 
{
		Break while loop
}
}
End game;
}
}
}

