# BeepBoop

## Multiplayer Game Development

This project marks my first experience with programming a networked multiplayer game. The added complexity of developing a networked game has proven to be a fun and exciting challenge in my game development journey!

## Game Design

For this project, I adhere to three simple design motifs: **Toy Box**, **Embrace Distraction**, and **Comical**. Throughout development, I design puzzles and interactable objects that align with these motifs and scale for multiple players.

## Game Engine

Most of my game development projects have been done using Unity. However, for this project, I decided to switch to **Unreal Engine** to leverage high-fidelity assets and strengthen my C++ skills. Thankfully, many systems between the two engines are similar, allowing me to apply the skills I've learned in Unity to this project.

## C++ Emote System

As this project is still a work in progress, the videos showcase game mechanics and designs as they are developed.

## Dev Log

To align with the design motifs of **Comedy** and **Embracing Distraction**, I developed an emote system that enables players to interact and have fun with each other while navigating the game world. This system involves creating a functional UI menu, configuring the player's animation state machine, and ensuring animations replicate correctly to each connected client.

## Pressure Plates

I developed a pressure plate system to enhance game interactivity. These plates can be used as switches, linked to other game objects or events, and triggered by players or objects. This system is ideal for doors, platforms, and generating in-game events.

## Creating & Joining a Server

Unreal Engine utilizes a client-server model to run games across multiple machines. One machine acts as a **listen server**, allowing players with the right credentials to connect as clients and run the simulation. I leveraged Unreal Engine's multiplayer subsystem to build functionality for creating and joining game sessions, where one player hosts the game server on their machine, and others connect as clients.
