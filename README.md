# SIR Model

Last year I tried to learn about epidemiological models, starting with Susceptible Infectious Recovered (SIR) [1](https://en.wikipedia.org/wiki/Compartmental_models_in_epidemiology). I tried to solve the equations using the Euler Method, but it did not went well. The Euler Method don't keep the population constant, this can be seen _"sir_euler_total_pop.png"_. So I used the GSL to solve de coupled equations, the graphs can be seen in the _"sir_rk45_curves.png"_. 

Later I did an dynamical code, where the particles move in a matrix. If a susceptible became neighbour with an infected it turns to infected. After some time the infected become recovered. One can be check the simulation in the _"sir_dynamics_rw.gif"_, where purple is Susceptible, orange is Infectious and green is Recovered. There is some problem with this code, that I will work it on some day, the particles can move in diagonal. In a Random Walker model they can only move in vertical or horizontal. This can mess up my results. The curves of this dynamical simulation has some resemblance of the continous simulations.

In all my models the particles/persons cannot die. 

All comments are in portuguese.
