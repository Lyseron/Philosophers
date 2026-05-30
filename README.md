*This project was created as part of the 42 curriculum by **lyaberge**.*

# Philosophers

## Description

**Philosophers** is a 42 project that introduces the basics of concurrent programming.

The goal is to simulate the famous **Dining Philosophers Problem**, where several philosophers share forks, eat, sleep, and think, while avoiding problems such as:

* deadlocks
* data races
* corrupted shared data
* mixed or incorrect output

Each philosopher is represented by a thread.
To eat, a philosopher must take two forks. Each fork is protected by a mutex.

The program stops when:

* a philosopher dies because they did not eat in time, or
* every philosopher has eaten the required number of meals, if this optional argument is provided.

## How it works

Each philosopher follows a loop:

```txt
eat → sleep → think
```

A monitor checks the stopping conditions during the simulation.

The program must carefully manage shared resources because several threads are running at the same time.

## My implementation

To avoid **deadlocks** and circular waiting, philosophers do not all take their forks in the same order.

* Even-numbered philosophers take the right fork first, then the left fork.
* Odd-numbered philosophers take the left fork first, then the right fork.

This prevents every philosopher from locking the same type of fork first and waiting forever for the second one.

To avoid **data races**, I used mutexes to protect shared data:

| Mutex        | Purpose                                                                 |
| ------------ | ----------------------------------------------------------------------- |
| `lock_meal`  | Protects each philosopher's `last_meal` time and number of meals eaten. |
| `lock_print` | Protects printed output so messages do not mix together.                |
| `lock_dead`  | Protects the shared stop/death state of the simulation.                 |

## Key concepts

### Data race

A data race happens when multiple threads read or write the same shared data at the same time without proper protection.

This can create unpredictable behavior.

### Deadlock

A deadlock happens when two or more threads wait forever for resources held by each other.

In this project, this could happen if every philosopher takes one fork and waits forever for the second one.

### Data corruption

Data corruption can happen as a consequence of data races.

If several threads modify the same variable at the same time without a mutex, the final value can become incorrect or unpredictable.

## Program arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument                                    | Description                                                                                     |
| ------------------------------------------- | ----------------------------------------------------------------------------------------------- |
| `number_of_philosophers`                    | Number of philosophers and forks.                                                               |
| `time_to_die`                               | Maximum time in milliseconds a philosopher can stay without eating.                             |
| `time_to_eat`                               | Time in milliseconds a philosopher spends eating.                                               |
| `time_to_sleep`                             | Time in milliseconds a philosopher spends sleeping.                                             |
| `number_of_times_each_philosopher_must_eat` | Optional argument. The program stops when every philosopher has eaten at least this many times. |

## Compilation

To create the executable:

```bash
make
```

This creates the `philo` executable.

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Test examples

### Philosophers should not die

```bash
./philo 2 800 200 200
```

### A philosopher should die

```bash
./philo 2 400 100 100
```

### Each philosopher should eat at least 3 times

```bash
./philo 2 800 200 200 3 | grep "is eating" | wc -l
```

Expected result:

```txt
6
```

Because there are 2 philosophers and each one must eat 3 times.

### A philosopher should die around 110 ms

```bash
./philo 1 110 100 100
```

With only one philosopher, there is only one fork, so the philosopher cannot eat and should eventually die.

## Skills practiced

* C programming
* Threads
* Mutexes
* Concurrent programming
* Shared data protection
* Deadlock prevention
* Data race prevention
* Time management
* Monitoring threads
* Memory management
* Debugging synchronization issues

## Resources

I used resources to understand the concepts behind threads, mutexes, and concurrent programming.

* IBM documentation about mutexes
* Codequoi article about threads and mutexes in C
* ENS Lyon course material about C threads
* CodeVault YouTube videos about threads and mutexes

## AI use

I used AI as a learning and debugging tool, never to generate the final code.

I always started my prompts with a strict no-code rule, asking only for explanations, as if another student was teaching me.

I mostly used AI to:

* better understand timing issues with `usleep`
* help design a more precise sleep function
* debug mutex destruction and memory cleanup
* understand possible causes of segmentation faults
* identify weak points in my logic by testing failure scenarios
* help write this README in English
