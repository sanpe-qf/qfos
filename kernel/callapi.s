		EXPORT	Kernel_Mode
		EXPORT	Kill_Auto
		EXPORT	Kill_Thread
		EXPORT	Enter_Critial	
		EXPORT	Exit_Critial
			
		AREA |.text|, CODE
		PRESERVE8 
        THUMB 
Kernel_Mode
	SVC 1
	BX	LR
	
Kill_Auto
	SVC 2
	BX	LR	
	
Kill_Thread
	SVC 3
	BX	LR
	
Enter_Critial
	SVC 4
	BX	LR	
	
Exit_Critial
	SVC	5
	BX 	LR
	
	END
			