# Dining Philosophers Problem

## Overview
The code is an implementation of the dining philosophers problem in C using semaphores and threads. It aims to break the hold and wait condition as well as the circular wait condition that can occur in the problem. It creates five threads to represent five philosophers, and uses semaphores to represent chopsticks. The code randomly selects which chopstick a philosopher will try to pick up first, and if one of the chopsticks is not available, the philosopher puts down the chopstick they are holding and waits for a random period of time before trying again.
