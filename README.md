Helicopter Side Scroller Game

Note: There are so many hacks in here. I should probably fix them and implement them better. However, because this is due tomorrow (friday, Jan 24, 2013) and they won't check the code structure, I'll leave it as is. I am however still ashamed at the ugliness of this code. I expected better. I was just somewhat lazy.

Enhancements:

Gameplay
    - created a new aircraft turrets with somewhat predictable flight patterns. 
    - Added Turrets that shoot back with some artificial intelligence (aimbot). They will only shoot if the user is within a certain distance from the turret.
    - Scoring mechanism
        - created a score counter that is incremented whenever the player destroys an enemy turret (1 point) and enemy aircrafts (3 points)
    - implemented double buffering
    - Increasing and Decreasing the speed of the game
    - God Mode (No collision against the helichopter) press     - Created a snowflake bomb by pressing "N". The player can press N up to 3 times.

Maps
    - Randomly generate a map as the game progresses.
    - Randomly increase or decrease the height of the next building by 1 or 2 blocks or by staying the same.
    - Randomly generates where the turrets are placed
    - Make sure that the aircrafts don't hit the buildings.
