# Dining Philosophers Problem
This is a solution to the dining philosophers problem in C using pthreads and semaphores.

## Overview
The code is an implementation of the dining philosophers problem in C using semaphores and threads. It aims to break the hold and wait condition as well as the circular wait condition that can occur in the problem.

The program creates 5 philosopher threads and initializes 5 semaphores for the chopsticks. Each philosopher thread goes through a loop where they alternate between thinking and eating. When a philosopher wants to eat, they first try to pick up the chopstick on their right, except for philosopher 0 who picks up the right chopstick first to break the circular wait condition.

If the right chopstick is not available, the philosopher puts down the chopstick they have picked up and waits for a random amount of time before trying again. 

If the right chopstick is available, the philosopher picks it up and tries to pick up the chopstick on their left.

If the left chopstick is not available, the philosopher puts down both chopsticks and waits for a random amount of time before trying again. 
 
If the left chopstick is available, the philosopher picks it up and starts eating for a random amount of time before putting down both chopsticks.

