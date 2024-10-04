## 1. **Introduction**
### Purpose
This documents outlines the functional and non-functional requirements for the text chat system in Beep Boop.
### Scope
In-game text communication feature that allows players to send and view messages in a global chat box.

## 2. **System Overview**
### System Description 
This system will provide a chat box in the lower left corner of the player's HUD which can be used for real-time communication. The chat box will take a small amount of space to prevent HUD bloat, but will have the ability to expand for a larger view of chat history.
### Assumptions


#### 1. **Game Environment Assumptions**
   - **Multiplayer Environment**: The game will have a multiplayer setup where players are connected through shared game sessions.
   - **Fixed Player Limit**: Each game session will have a maximum of X players, which ensures that the chat system doesn’t need to scale indefinitely.
   - **Dedicated Chat Interface**: There will be a dedicated interface for displaying and entering chat messages that doesn’t obstruct gameplay.
   - **Game Focused on Robots**: Since the game revolves around robots, the chat system should align with the aesthetic and functionality of the overall game design.
   - **Interaction Zones**: Players can interact through chat regardless of their physical proximity in the game world.
   - **No Voice Chat Integration**: The assumption is that the game will rely purely on text-based communication, not requiring a voice chat system.

#### 2. **Network Assumptions**
   - **Sufficient Bandwidth**: The text-based chat system will consume minimal bandwidth compared to other in-game activities like rendering or physics calculations, so it won't cause significant performance issues.
   - **Persistent Connection**: Players remain connected to the server throughout the game session, and the chat system should handle brief disconnections without losing messages.

#### 3. **User Assumptions**
   - **Players Are Familiar with Chat Systems**: It is assumed that players have used similar text-based chat systems in other multiplayer games, so the interface doesn’t require extensive tutorials.
   - **Keyboard Support**: Since Beep Boop is being developed exclusively for PC, users will be entering messages via keyboard.
   - **Multilingual Player Base**: Some players may communicate in different languages, and the system should handle non-English characters without issues.
   - **Player Behavior**: While most players will use the chat system responsibly, there is an assumption that chat filtering will be needed for inappropriate language or spam prevention.
   - **Dependencies**: Unreal Engine, Multiplayer Framework, Server Communication, User Interface (UI).

## 3. **Functional Requirements**
   ### 3.1 **Core Functionality**
   - **Text Message Sending**: Players can send messages to the global chat box.
   - **Text Message Viewing**: Players can view messages sent by others in in the global chat box.
   - **Message Formatting**: Support for text formatting (colors, emojis, etc.). (Nice to have)
   - **Chat Filtering**: Filtering inappropriate language or spam detection.

   ### 3.2 **User Interface**
   - **Chatbox**: Chat box in the lower left corner of the player's HUD. Can be in a minimized or expanded state.
   - **Message Display**: Messages are displayed in the the chat box. When the chat box is minimized, the chat box will only display up to 5 of the most recent messages. When the chat box is expanded, it will display as many messages as can fit in the expanded UI widget (size still to be determined).
   - **User Input**: Player's will be able to click on the message bar, or press enter to initiate the message sending process. Players will be able to use the mouse wheel to scroll up and down through the message log when the chat box is expanded. The player can click outside of the chat box or press enter again to minimize the widget.
   
   ### 3.3 **User Management**
   - **Mute/Block Players**: Ability for users to mute/block other players.

## 4. **Non-Functional Requirements**
   - **Usability**: Easy to use interface, no more than two clicks to send a message.
   - **Localization**: Support for multiple languages.
   - **Accessibility**: For now, being able to change the font size will be the only available accessibility feature.

