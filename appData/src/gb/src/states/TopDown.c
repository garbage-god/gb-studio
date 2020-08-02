// clang-format off
#pragma bank 5
// clang-format on

#include "states/TopDown.h"
#include "Scroll.h"
#include "Input.h"
#include "Collision.h"
#include "Actor.h"
#include "Trigger.h"
#include "GameTime.h"
#include "ScriptRunner.h"
#include "Camera.h"
#include "rand.h"

void Start_TopDown() {
  // Set camera to follow player
  camera_offset.x = 0;
  camera_offset.y = 0;
  camera_deadzone.x = 0;
  camera_deadzone.y = 0;
}

void Update_TopDown() {
  UBYTE tile_x, tile_y, hit_actor, hit_trigger;

  tile_x = player.pos.x >> 3;
  tile_y = player.pos.y >> 3;

  if (PlayerOnTile()) {
    // If player was moving on the previous frame
    if (player.moving) {
      // Check for trigger collisions
      if (ActivateTriggerAt(tile_x, tile_y)) {
        // Landed on a trigger
        PlayerStopMovement();
        return;
      }
    }

    // Player landed on an 8x8px tile
    // so stop movement for now
    PlayerStopMovement();

    // Check input to set player movement
    if (INPUT_RECENT_LEFT) {
      PlayerSetMovement(-1, 0);
    } else if (INPUT_RECENT_RIGHT) {
      PlayerSetMovement(1, 0);
    } else if (INPUT_RECENT_UP) {
      PlayerSetMovement(0, -1);
    } else if (INPUT_RECENT_DOWN) {
      PlayerSetMovement(0, 1);
    }

    if (INPUT_A_PRESSED) {
      // Find actor in front of player
      hit_actor = ActorInFrontOfPlayer();

      if (hit_actor != NO_ACTOR_COLLISON && !actors[hit_actor].collision_group) {
        // Turn actor to face player
        actors[hit_actor].dir.x = -player.dir.x;
        actors[hit_actor].dir.y = -player.dir.y;
        actors[hit_actor].rerender = TRUE;

        // Stop player from moving
        PlayerStopMovement();

        // Run actors interact script
        ActorRunScript(hit_actor);
      }
    }
  }
}
