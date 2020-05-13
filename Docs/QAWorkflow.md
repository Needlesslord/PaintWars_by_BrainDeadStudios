# QA WORKFLOW


***


## Main Index

+ [Introduction](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#introduction)

+ [Tools Used](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#tools-used)

+ [Workflows](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#workflows)
  - [Pre-production](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#pre-production)
  - [Alpha](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#alpha)
  - [Gold](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#gold)
  
+ [Software](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#software)

+ [Milestone Delivery Protocol](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#milestone-delivery-protocolhttps://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#milestone-delivery-protocol)
  - [Internal Milestones](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#internal-milestones)
  - [External Milestones](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#external-milestones)
  
+ [Bug Properties](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#bug-properties)

+ [Process for Quality Testing](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#process-for-quality-testing)

+ [Process for Quality Assurance](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#process-for-quality-assurance)
  - [Internal QA Test](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#internal-qa-test)
  - [External QA Test](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/QAWorkflow.md#external-qa-test)


***


## Introduction


In this section, the Quality Assurance (QA) plan, we'll be explaining the tools, methods, parameters and tests that we'll be using during the developement of our video game project.


***


## Tools Used


We will use Github issues as a tool to report bugs. In order to report a bug we just have to press the button “New issue”, and fill the template provided by the tool to describe everything about the bug, what happens, when it happens, complexity, priority… A label can be added, if necessary, to provide some more information about the bug. Each bug report, must follow all the specified parameters of our template.


***


## Workflows 

This is the workflow the team will use:

![image](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/Photos_Wiki/workflows.png)

As we can see, the QA is involved in all the process of the project.

### Pre-production

During this process, the QA members will test the prototype (Vertical Slice) that the team will be doing and see if everything works as expected. This means that the buildings and troops and all the other parts of the game will have to work as the team wants, if not, the team will have to fix everything that the QA members have reported.

### Alpha

Here the QA team will try the Alpha of the game and they will report any bug or any issue that can be improved. For example, that the map works well, the economy of the game is well-balanced and this sort of things to be optimized for the Gold version.

### Gold

In this final process, it has to be tested everything that has been optimized to see if it is better optimized than the Alpha version and if it works more fluid. Because in this part not only has to be tested if everything works fine, also if the game produces the expected feelings.

***


## Software


The software we will use it will be Github Issues. We will create a template on Github Issues that will help us to control the bugs and fix them.


***


## Milestone Delivery Protocol


### Internal Milestones


Every friday, we will make a build and, on Saturday, it will be tested in a QA test sesion. Finally, the bugs will be fixed and retested between Sunday and Monday. In this session, the QA team and the Team Lead will test the game. Every two weeks, we will test the game with another team and see which aspects of our game can be improved with their help.


### External Milestones


All the external milestones will be organised a week before every delivery. This milestones will consist in a major QA test session where all the members of the team will take part in. After this milestones, the team will make the necessary changes in order to improve the game.

The deliveries are:

**Vertical Slice:** 19th April

**Alpha:** 16th May

**Gold:** 30th May


***


## Bug Properties


For describing the bugs we will use a template like the following one:

![Image](Photos_Wiki/Github_Issues_Template.jpg)

+ **Bug Title:** Brief description about what happens.
+ **Summary:** Description more explained.
+ **Status:** It tells if the bug has been fixed or it is still happening.
+ **Type:**
  - A: Game breaking bug or bug that makes the game unplayable.
  - B: Bug that makes the game less playable as intended.
  - C: Aesthetic, graphical or audio bug.
+ **Priority:**
  - Urgent: Bug needs to be fixed immediately.
  - High: Bug needs to be fixed within a day or two. 
  - Regular: Bug needs to be fixed within a week.
  - Low: Bug needs to be fixed whenever there aren't any high or urgent bugs.
+ **Frequency:**
  - Always.
  - High.
  - Regular.
  - Low.
+ **Steps to reproduce:** It says how to arrive to the bug.
+ **Actual result:** It is what happens.
+ **Expected result:** It is what it should happen.
+ **Build:** Build where the bug happens.
+ **Screenshot or video:** A screenshot or video of the bug to know how it is.

***


## Process for Quality Testing

Quality Tests are made by external people of the team to ensure the game is as fun as intended. Testers have to be sincere people, preferably people not related to the team members. Testers will be proposed by any member of the group the week before the Quality Test. The tester needs to be someone who doesn't play videogames casually. The team will decide if that person is adequate to test the game. In case that the team has conflict choosing a tester, the QA manager will be who has the last word. The tester will be contacted, and if he/she accepts to be tester, the tester and the test holder (can be anyone from the team) will specify a day and hour to perform the test.

How the test will go:
+ Presentation (2 min)

+ Pre game questions (5 min)
  - Which is their favourite genre.
  - Do they like/play Warcraft or any other RTS video game.
  
+ Core playtest (20 min)
  - Thinking aloud method will be the one used (the tester speaks what they think while playing the game).
  - The tester is observed by the test holder.
  - The test holder will have minimum interaction with the tester.
  - Test holder takes notes.
  
+ Post game questionary (10 min)
  - What the tester thinks about the game in general.
  - What they would improve about the game.
  - What they would keep.
  
+ Thanks and send-off (2 min)

After the Quality Test, the test holder will put together everything the tester said and present to the team how the playtesting went. Then, it will be decided if there should be some design change or not. If the team has a conflict regarding the change of something in the game, the head designer of the team will have the last word regarding this problem.

***


## Process for Quality Assurance


### Internal QA Test


Every friday, a build will be made. This build will be tested with a QA test on saturdays. The normal tests will last approximately 1 hour while the big ones 1 hour and a half, more or less. All bugs must be reported using the template explained before with Github issues. After the session, the QA master will check that the reports have been well done and will pass all the informations to the members of the team. All bugs will be fixed during sundays and mondays.

When a bug is found, we will follow this process:

![image](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/Photos_Wiki/qa%20process.png)


### External QA Test


This test are similar than the internal QA tests, but instead of being done by members of the team, this test is performed by other people, in our case, other groups. This will help to find bugs the ones couldn’t be found by the members of the team.


***







