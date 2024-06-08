#pragma once
#include "../Components/GhostRenderer.h"
#include "../Components/PacmanMovement.h"

namespace bdnE
{
	class GameObject;
}

namespace bdnG {

	class GhostState
	{
	public:
		GhostState() = default;
		virtual ~GhostState() = default;
		GhostState(const GhostState&) = delete;
		GhostState(GhostState&&) = delete;
		GhostState& operator=(const GhostState&) = delete;
		GhostState& operator=(GhostState&&) = delete;

		virtual void Enter(bdnE::GameObject* pacman) = 0;
		virtual void Exit() = 0;
		virtual GhostState* Update(bdnE::GameObject* owner, bdnE::GameObject* pacman, bdnG::PacmanMovement* moveComponent) = 0;
		virtual void Render(GhostRenderer* renderer) = 0;
	};
}

// +----------------------------------------------------------------------------------+                        
// |GHOST                                                                             |                        
// |                                                                                  |                        
// |                                                                                  |                        
// |                                                                                  |                        
// |                                                                                  |                        
// |                                                                                  |                        
// |                             +-------------------------------------------------+  |                        
// |                             | SEARCHING                                       |  |                        
// |                             |                                                 |  |                        
// |                             |                 20 seconds pass                 |  |                        
// |                     Packman |                                                 |  |                        
// |                     picks up|            +----------------------+             |  |                        
// |                     powerup |            |                      |             |  |                        
// |     +------------+          |    +-------+--------+    +--------v--------+    |  |                        
// |     | FRIGHTENED |<---------+    | CHASE          |    | SCATTER         |    |  |                        
// |     |            |          |    |                |    |                 |    |  |  +-------+             
// |     |  Move      |          |    |  Move to tile  |    |   Move to       |<---+--+--+ START |             
// |     |  slow down |          |    |  near pacman   |    |   predetermined |    |  |  +-------+             
// |     |            +--------->|    |                |    |   tile          |    |  |                        
// |     +------+-----+          |    |                |    |                 |    |  |                        
// |            |        10 sec  |    +--------^-------+    +--------+--------+    |  |                        
// |     Hit by |        pass    |             |                     |             |  |                        
// |     pacman |                |             +---------------------+             |  |                        
// |            |                |                                                 |  |                        
// |            |                |                 5-7 seconds pass                |  |                        
// |     +------v--------+       |                                                 |  |                        
// |     | DEAD          |       +-------------------------^-----------------------+  |                        
// |     |               |                                 |                          |                        
// |     |   Move to     +---------------------------------+                          |                        
// |     |   ghost house |          Enters ghost house                                |                        
// |     |               |                                                            |                        
// |     +---------------+                                                            |                        
// |                                                                                  |                        
// +----------------------------------------------------------------------------------+                        
//                                                                                                             
//                                                                                                             
//                                                                                                             
//  SOURCE:https://www.mentalfloss.com/article/90874/your-pac-man-game-learning-different-strategies-each-ghost
//         https://gameinternals.com/understanding-pac-man-ghost-behavior       