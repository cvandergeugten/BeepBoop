# BeepBoop

<p align="center">
  <img width="460" height="300" src="[https://github.com/cvandergeugten/Ninja-Game/blob/main/ProjectImages/Ninja_Game_Heading.gif](https://github.com/cvandergeugten/BeepBoop/blob/main/RepoImages/Robot_Wave.png)">
</p>

## Overview

**BeepBoop** is my first networked multiplayer game development project, presenting an exciting challenge in my game development journey. This project allows me to explore the complexities of online gameplay while creating an engaging experience for players.

## Game Design Principles

In crafting BeepBoop, I focus on three key design motifs:
- **Toy Box:** Creating a playful environment where players can experiment and enjoy themselves.
- **Embrace Distraction:** Incorporating fun, whimsical elements that keep players engaged and entertained.
- **Comical:** Ensuring that humor is woven into the gameplay through lighthearted puzzles and interactions.

## Game Engine

While most of my previous projects were developed in **Unity**, I chose to use **Unreal Engine** for BeepBoop. This transition allows me to leverage high-fidelity assets and strengthen my C++ skills, as I adapt the foundational knowledge from Unity to Unreal's environment.

## Core Features

### Emote System
To promote interaction and engagement among players, I implemented an **Emote System**. This system allows players to express themselves and have fun while navigating the game world. Key components include:
- A functional **UI menu** for selecting emotes.
- A configured **animation state machine** to manage player animations.
- **Animation replication** to ensure consistent experiences across all connected clients.

### Pressure Plate Mechanic
I developed a **Pressure Plate System** to enhance interactivity within the game. Features include:
- Functionality as switches for various in-game events.
- Capability to link with other game objects, like doors and platforms.
- Triggering by player actions or interactions with other objects, fostering dynamic gameplay experiences.

## Networking and Server Architecture

BeepBoop utilizes a **client-server model** to facilitate multiplayer interactions across different machines:
- One machine acts as a **listen server**, allowing players to connect as clients.
- I leveraged Unreal Engine's **multiplayer subsystem** to create and join game sessions seamlessly.
- Players can host game servers on their machines, enabling others to join and participate in the game.
