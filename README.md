# PID Controls
---

**PID Controls Project**

The goals / steps of this project are the following:

* The PID procedure follows what was taught in the lessons
* Description of the effect each of the P, I, D components in the implementation
* Description of how the final hyperparameters were chosen
* The vehicle must successfully drive a lap around the track

[//]: # (References)
[simulator]: https://github.com/udacity/self-driving-car-sim/releases
[win 10 update]: https://support.microsoft.com/de-de/help/4028685/windows-get-the-windows-10-creators-update
[uWebSocketIO]: https://github.com/uWebSockets/uWebSockets
[linux on win 10]: https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/
[MinGW]: http://www.mingw.org/
[CMake]: https://cmake.org/install/
[udacity code]: https://github.com/udacity/CarND-PID-Control-Project
[pid ressource]: https://udacity-reviews-uploads.s3.amazonaws.com/_attachments/41330/1493863065/pid_control_document.pdf
[output video]: ./imgs/pid-controls.mp4 "PID Controls Project Video"

---

## Files Submitted & Code Quality

### 1. Submission includes all required files and every TODO task has been accomplished 

For this project, I have used the [PID Controls Project Starter Code][udacity code] from Udacity and I have modified the following three files:
```cpp
main.cpp
PID.cpp
PID.h
```

The ```PID.cpp``` file has all the core logic for the PID controls. The `void PID::Init()` on line 15 initializes the P, I & D errors, and coefficients. The void `PID::UpdateError()` function on line 30 retrieves the CTE (Cross Track Error) and updates the P, I & D errors on each step in the simulator. If Twiddle-fine-tuning is activated the `void PID::Twiddle()` function on line 48 is called and the coefficients `Kp`, `Ki` and `Kd` are updated/fine-tuned with the Twiddle algorithm from Sebastian Thrun. The Twiddle algorithm starts after 300 steps (after the vehicle is not accelerating anymore) and stops after 1800 steps (before the turn in the road) in the simulator. Finally, the steering value/total error is calculated and returned from the `double PID::TotalError()` function on line 44.

### 2. Code must compile without errors

This project was done on Windows 10. In order to set up this project I had to:
* update my Windows 10 Version with the [Windows 10 Creators Update][win 10 update]
* install the [Linux Bash Shell][linux on win 10] (with Ubuntu 16.04) for Windows 10
* set up and install [uWebSocketIO][uWebSocketIO] through the Linux Bash Shell for Windows 10
* [download the simulator from Udacity][simulator]

**To update the Linux Bash Shell to Ubuntu 16.04 the Windows 10 Creators Update has to be installed!**

Also, [CMake][CMake] and a gcc/g++ compiler like [MinGW][MinGW] is required in order to compile and build the project.

Once the install for uWebSocketIO is complete, the main program can be built and run by doing the following from the project top directory in the Linux Bash Shell.

1. `mkdir build`
2. `cd build`
3. `cmake .. -G "Unix Makefiles" && make` on Windows 10 or `cmake .. && make` on Linux or Mac
4. `./pid`

Then the simulator has to be started and *Project 4: PID Controller* has to be selected. When everything is set up the Linux Bash Shell should print: 
```bash 
Listening to Port 4567
Connected
```

### 3. Effect of each P, I, D components and decision of choosing final hyperparameters

Firstly, the hyperparameters were tuned manually leading to initial hyperparameters of `Kp = 0.11, Ki = 0.00004, Kd = 1.2`. Secondly, the hyperparameters were fine-tuned by the Twiddle algorithm to `Kp = 0.131, Ki = 0.011, Kd = 1.32`. And lastly, the coefficient `Ki` was again manually fine-tuned leading to the final hyperparameters of `Kp = 0.131, Ki = 0.00011, Kd = 1.32`. The last fine-tuning process of the coefficient `Ki` was necessary because the vehicle steered too aggressively and therefore left the road. A too low value of `Kd` had the effect that the vehicle didn't react fast enough to a turn in the road so the vehicle either (nearly) left the road or the steering was not smooth at all.
The following resource gave me good hints for manually tuning the hyperparameters: [An introduction and tutorial for PID controllers, by George Gillard][pid ressource].

### 4. Final Output:

[Link to the video of the final output][output video]

Note: This video is accelerated and does not match with the actual speed during this recording.

---

## Discussion

### 1. Briefly discuss any problems / issues you faced in your implementation of this project.

I had issues to get my Twiddle algorithm up and running for hyperparameter fine-tuning. When I decided to use the algorithm, the vehicle steered to the right instantly and left the road. Because I used the Twiddle algorithm from Sebastian Thrun without modification, only the first coefficient `Kp` was tuned and the other coefficients stayed the same. So I had to modify the algorithm slightly in order to run properly.