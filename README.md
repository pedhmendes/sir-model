# SIR Model

Last year (2020) I tried to learn about epidemiological models, starting with Susceptible Infectious Recovered (SIR) [1](https://en.wikipedia.org/wiki/Compartmental_models_in_epidemiology). I tried to solve the equations using the Euler Method, but it did not went well. The Euler Method don't keep the population constant, this can be seen in the _"euler_populacao.png"_. So I used the GSL to solve de coupled equations, the graphs can be seen in the _"rkf_B*.png"_. 

Later I did an dynamical code, where the particles move in a matrix. If a susceptible became neighbour with an infected it turns to infected. After some time the infected become recovered. One can be check the simulation in the _"dynamics.gif"_, where purple is Susceptible, orange is Infectious and green is Recovered. The curves of this dynamical simulation have some resemblance of the continous simulations.

In all my models the particles/persons cannot die. 

All comments are in portuguese.

# Update / Presentation
I did a presentation about SIR Model for Introduction to Dynamical Systems. The pdf and tex source can be found in this repo.

I also updated the codes, there is new plots and gifs.
