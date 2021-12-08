# Simon Stores Code v1.2

Simon Stores is a complex math problem in the game Keep Talking and Nobody Explodes

----
#### [Link to instrustions](https://ktane.timwi.de/HTML/Simon%20Stores.html)

This is a c++ script that I wrote that is capable of sloving it

The main feature of this puzzle being a balanced ternary conversion 

More details can be found in this [repository](https://github.com/BrandonPacewic/BalancedTernaryConverter)

----

![pic](https://github.com/BrandonPacewic/SimonStores/blob/master/images/simonStores.jpeg)

----

### Project Directory

```bash
main.cc
└── local.hpp
	├── balancedTernaryConverter
	│  	└── balancedTernaryConverter.hpp
	│  
	├── math
	│	├── math.hpp
	│	└── modulo.hpp	
	│
	├── modualRuleSet
	│	├── colorSequence.hpp	
	│	└── initalCalculations.hpp
	│
	├── stageFunctions
	│	├── stageOne.hpp 
	│	├── stageTwo.hpp
	│	└── stageThree.hpp	
	│
	└── userInput	
		├── userErrorCatch
		│	└── userErrorCatch.hpp	
		└── userMenu.hpp
```

----

### A lizard is not a valid input

As a added bonus parts of this program will accept a 6 character string which allows for the input of lizard

This is of course compleatly unnaceptable and needed to be fixed 

![lizard](https://github.com/BrandonPacewic/SimonStores/blob/master/images/lizardIsNotAValidInput.png)
