# FractalTreeOLC
Simple script to generate a fractal tree. 
Hardest part was getting the rotation to work. If I'm not mistaken c++ does not come with a "rotation" function that does the work for you like some other languages out there. Feel free to improve upon it. One thing to try is making the angle interpolate between two values - see how it changes the tree.

Add this if you want 3 branches. Keep in mind this will slow down the performance exponentially if the limit is high.

      float aX = end.x + std::sin(angle + branchAngle) * distance * branchHeightRatio;
			float aY = end.y + std::cos(angle + branchAngle) * distance * branchHeightRatio;
														 
			float bX = end.x + std::sin(angle - branchAngle) * distance * branchHeightRatio;
			float bY = end.y + std::cos(angle - branchAngle) * distance * branchHeightRatio;

			float cX = end.x + std::sin(angle) * distance * branchHeightRatio;
			float cY = end.y + std::cos(angle) * distance * branchHeightRatio;
			
			DrawBranch(end, olc::Vector2(aX, aY), limit - 1);
			DrawBranch(end, olc::Vector2(cX, cY), limit - 1);
			DrawBranch(end, olc::Vector2(bX, bY), limit - 1);
