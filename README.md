# The Lasso Game

A simple game developed in C++ where you "lasso" around the moving lasso head to catch coins if they are in the specified region around the head. <br>
## Game features
* The coin is shot upwards at a randomized angle from a cannon which is set a little distance away from where the lasso head emerges. <br> </ls>
* The angle at which the lasso head is thrown towards the coin can be adjusted using controls. <br>
* The game has levels, and progression to the next requires a certain number of coins to be caught, which is the level quest. <br>
* Bombs are thrown every second level and catching one deducts 1 from the player's total score. <br> 
* Magnets are thrown every third level after completing half of the level quest and catching one doubles the Lasso catch radius for the rest of the level, for the rest of the level, which makes catching coins a bit easier. This Magnet is thrown only once, and if not caught will not appear again in that level. <br>
* All moving objects (Lasso head, Coins, Magnets and Bombs) follow "gravitational" acceleration and follow parabolic paths. <br>
* The controls of the game are described as text within the game window, on the top right. <br>
