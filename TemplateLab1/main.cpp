#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv)
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");

	sf::RectangleShape body(sf::Vector2<float>(10.0f, 30.0f));
	sf::RectangleShape neck(sf::Vector2<float>(2.2f, 5.0f));
	sf::CircleShape headCirc(3, 100);
	sf::RectangleShape lowerArmRect(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape upperArmRect(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape lowerArmRect2(sf::Vector2<float>(-15.0f, -5.0f));
	sf::RectangleShape upperArmRect2(sf::Vector2<float>(-15.0f, -5.0f));

	body.setFillColor(sf::Color::Magenta);
	neck.setFillColor(sf::Color::Green);
	headCirc.setFillColor(sf::Color::Yellow);
	lowerArmRect.setFillColor(sf::Color::Blue);
	upperArmRect.setFillColor(sf::Color::Red);
	lowerArmRect2.setFillColor(sf::Color::Blue);
	upperArmRect2.setFillColor(sf::Color::Red);
	bool keyHeld = false;

	bool growing = true;
	float scaleFactor = 1.001;

	float growthFactor = 1.001f;
	float shrinkFactor = 0.999f;

	//body.setOrigin(10, 10);
	body.setOrigin(body.getLocalBounds().width/2, body.getLocalBounds().height);
	body.setPosition(300, 300);
	body.setScale(4, 4);

	neck.setPosition((body.getLocalBounds().width / 4.0f), (body.getLocalBounds().height / 3.0f));
	neck.setScale(2, 2);
	neck.setOrigin(0.0f, 10.0f);

	headCirc.setOrigin(0.0f, 1.0f);
	headCirc.setPosition(-2.0f, -4.5f);
	
	sf::Vector2<float> armPosition((body.getLocalBounds().width / 1.1f), (body.getLocalBounds().height / 3.5f));
	sf::Vector2<float> armOrigin(0.0f, 2.5f);

	sf::Vector2<float> armPosition2((body.getLocalBounds().width / 9.1f), (body.getLocalBounds().height / 2.5f));
	sf::Vector2<float> armOrigin2(0.0f,2.5f);

	upperArmRect.setOrigin(armOrigin);
	lowerArmRect.setOrigin(armOrigin);

	upperArmRect2.setOrigin(armOrigin2);
	lowerArmRect2.setOrigin(armOrigin2);

	lowerArmRect.setPosition(15.0f, 2.5f);
	upperArmRect.setPosition(armPosition);

	lowerArmRect2.setPosition(-15.0f, 2.5f);
	upperArmRect2.setPosition(armPosition2);

	TransformNode head(&headCirc);
	TransformNode neckTrans(&neck);
	TransformNode bodyTrans(&body);
	TransformNode upperArm(&upperArmRect);
	TransformNode lowerArm(&lowerArmRect);
	TransformNode upperArm2(&upperArmRect2);
	TransformNode lowerArm2(&lowerArmRect2);

	neckTrans.AddChild(&head);
	upperArm.AddChild(&lowerArm);
	upperArm2.AddChild(&lowerArm2);
	bodyTrans.AddChild(&upperArm);
	bodyTrans.AddChild(&upperArm2);
	bodyTrans.AddChild(&neckTrans);
	
	float elaspedTimeTotal = 0.0f;
	sf::Clock deltaTime;

	float bodyAngleCount = 0;
	float angleBodyAmount = 0;
	float fractional = 2.0f;
	double count = 1.0f;
	double remainInt = 0.0f;

	float angleAmountTotal= 0.0f;
	while (window.isOpen())
	{
	
		float elaspedTime = deltaTime.restart().asSeconds();
		//elaspedTimeTotal = elaspedTimeTotal + elaspedTime;
		sf::Transform transform = body.getTransform();

		/*body.scale(scaleFactor, scaleFactor);
		float currentScale = body.getScale().x;
		if (currentScale >= 4.0f) {
		scaleFactor = shrinkFactor;
		}
		else if (currentScale <= 1.0f)
		{
		scaleFactor = growthFactor;
		}*/

		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (sfEvent.type == sf::Event::KeyReleased)
			{
				keyHeld = false;
			}
			else if (sfEvent.type == sf::Event::KeyPressed)
			{
				keyHeld = true;
				
			}
		}
		
	
			if (keyHeld )
			{
				
					float angleAmount = 90.0f;
					angleBodyAmount = (angleAmount * elaspedTime);
					body.rotate(angleBodyAmount);
					lowerArmRect.rotate(angleAmount * elaspedTime);
					upperArmRect.rotate(angleAmount * elaspedTime);
					lowerArmRect2.rotate(-angleAmount * elaspedTime);
					upperArmRect2.rotate(-angleAmount * elaspedTime);
					
				
			
			}
			
		
		

		window.clear(); // draw fullscreen graphic

		/*sf::Transform hierarchy = sf::Transform::Identity;

		window.draw(body);
		hierarchy = hierarchy * body.getTransform();

		window.draw(lowerArmRect, hierarchy); // DRAWING with the body's transform.
		hierarchy = hierarchy * lowerArmRect.getTransform();

		window.draw(upperArmRect, hierarchy); // DRAWING*/

		bodyTrans.Draw(&window);

		window.display();
	}

	return 0;
}