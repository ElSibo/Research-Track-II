# Research-Track-II
 ## Doxygen
 #### brief description:  
 
 Doxygen is the de facto standard tool for generatingdocumentationfrom annotatedC++ sources, 
 butitalsosupports otherpopularprogramming languagessuchasC, Objective-C, C#, PHP, Java, Python, 
 IDL (Corba, Microsoft, and UNO/OpenOfficeflavors), Fortran, VHDL Doxygen                                                                 
 •It can generate an on-line documentation browser (in HTML) and/or an off-line reference manual (in LaTeX) 
 from a set of documented source files. 
 There is also support for generating output in RTF (MS-Word), PostScript, hyperlinked PDF, compressed HTML, and Unix man pages. 
 The documentation is extracted directly from the sources, 
 which makes it much easier to keep the documentation consistent with the source code.                                                              
 •You can configure doxygento extract the code structure from undocumented source files.                                                   
 This is very useful to quickly find your way in large source distributions. 
 Doxygencan also visualize the relations between the various elements by means of include dependency graphs, 
 inheritance diagrams, and collaboration diagrams, which are all generated automatically                                                      
 •You can also use doxygenfor creating normal documentation   
 
 #### what we do:
 
Our work on doxygen was essentially to create a documentation on the third assignment of RT1,                                                  
where we explained the functioning of the various scriprts and how they were connected to each other.                                   
for this work we could use sphinux or doxygen and we used doxygen as it was more convenient for scripts written in C ++.                            
In our case we had two scriprts which were cont_move.cpp and novi_goal_rob.cpp.

## Jupyter

#### brief description:

The Jupyter Notebook is an open source web application that you can use to create and share documents that contain live code, equations,
visualizations, and text. Jupyter Notebook is maintained by the people at Project Jupyter.
Project Jupyter is a non-profit, open-source project, 
born out of the IPython Project in 2014 as it evolved to support interactive data science 
and scientific computing across all programming languages
IPython (short for Interactive Python) was started in 2001 by Fernando Perez as an enhanced Python interpreter. 
As well as being a useful interactive interface to Python, 
IPython also provides a number of useful syntactic additions to the language. 
The Jupyter notebook is a browser-based graphical interface to the IPython shell, and builds on it a rich set of dynamic display capabilities.
Jupyter Notebooks are a spin-off project from the IPython project, which used to have an IPython Notebook project itself.
The Jupyter notebook is a browser-based graphical interface to the IPython shell, and builds on it a rich set of dynamic display capabilities.

#### what we do:

Generally our work on jupyter was to create an interactive interface with the user starting from the third assignment of RT1, 
where the user could control the robot directly from jupyter.                                       
To implement this it is necessary to understand how we had structured the third assignment of RT1, 
in order to understand how to proceed with the changes; 
in our case we had two nodes that communicated with the simulator, 
which were cont_move.cpp which managed the speeds that the robot had to assume during when it moved and the assistent control, 
and maintained continuous communication with the simulator.                                     
Then there was the navi_goal_rob.cpp Cher was essentially the user interface, 
taking input from the user and communicating directly with cont_move.cpp when changing the speed 
and with move_base when using the Go_toPoint () function.                                 
So in our case we had to rewrite this last node in jupyter, 
and instead of keyboard inputs we used wydgets, plus we reproduced the 3D view.

###   Navi_Goal_rob

   #### Description:

  this node allows for user three type of choise

  In the user interface with three choices:

  A) GO TO POINT: Where the user enters the coordinates of the point where the robot must go.

  B) CONTROLLER: Where the user moves the robot with a controller, but the robot can crash with obstacles.

  C) ASSISTENT CONTROLLER: where the user moves the robot with a controller, but the robot does not crash into obstacles, because it is equipped with laserscan which makes it stop near obstacles.

  and after reading the choise of user
  send it to other node

#### that is the library that we are used to implement the program
```py
#!/usr/bin/env python3

import rospy
from move_base_msgs.msg import MoveBaseAction
from move_base_msgs.msg import MoveBaseGoal
from geometry_msgs.msg import Point32
from nav_msgs.msg import Odometry
import actionlib
import time
from time import sleep 
import ipywidgets as widgets
from ipywidgets import Button, Layout, ButtonStyle, GridBox, VBox, HBox 
from IPython.display import display
from __future__ import print_function
from ipywidgets import interact, interactive, fixed, interact_manual 
import jupyros as jr
from jupyros import ros3d 
import os
```
###  goPoint()

  ####  Description:

    This function let the user insert the coordinate of the point and 
    if this cordinate are out of the perimeter request them again otherwise stop controller 
    and send the to server the coordinate then ask the user 
    if wont to calcel the goal and 
    if yes cancel the goal if no starting with timeout.
    in this function we have used two widgets floats test that take the desired coordinates 
    and two buttons one sends the goal and the other stops the function, 
    we have also added a widchet check to cancel the goal.

#### function that we used to implement the function go to point

    setX():
        function used for set the coordinate X of Goal
    setY():
        function  used for set the coordinate Y of Goal
    pos_rob():
        function  used for find the coordinate of the of the robot
    V_Cancel():
        function used for check the choice of the user for canceling Goal
    SendGoal():
        function  used for send the coordinate of Goal to the server MoveBase
    Timeout():
        function used for set the timeout and to cancel the Goal if user want it
    stopping():
        function used for stop the function go_Point with closing the widgets


###  controller()

####  Description:

This function read input of the user, and set the linear and angular velocity on /vel_cont and set the assistant control to on/off
function that we used to implement the function controller

  VLin():
      function used for set the linear velocity of robot
  VAng():
      function  used for set the Angular velocity of robot
  resetV():
      function  used for reset to 0 the velocity of the robot
  stopping():
      function used for stop the function controller with closing the widgets

  

