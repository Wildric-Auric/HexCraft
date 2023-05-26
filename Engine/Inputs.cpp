#include "glfw3.h"
#include "Inputs.h"
#include "Context.h"

KeyBoardMode Inputs::keyBoardMode = KeyBoardMode::INPUT_QWERTY;

int Inputs::KeyPressed(InputKey key) {
	return glfwGetKey((GLFWwindow*)Context::window, key) == GLFW_PRESS;
}




int Inputs::DirectionalKeyPressed(DirectionalKey key) {
	InputKey key0 = -1;
	switch (key) {
	case DirectionalKey::INPUT_RIGHT:
		if (Inputs::keyBoardMode == KeyBoardMode::INPUT_QWERTY)
			key0 = HEX_INPUT_KEY_D;
		else if (Inputs::keyBoardMode == KeyBoardMode::INPUT_AZERTY)
			key0 = HEX_INPUT_KEY_D;
		break;

	case DirectionalKey::INPUT_UP:
		if (Inputs::keyBoardMode == KeyBoardMode::INPUT_QWERTY)
			key0 = HEX_INPUT_KEY_W;
		else if (Inputs::keyBoardMode == KeyBoardMode::INPUT_AZERTY)
			key0 = HEX_INPUT_KEY_Z;

		break;

	case DirectionalKey::INPUT_LEFT:
		if (Inputs::keyBoardMode == KeyBoardMode::INPUT_QWERTY)
			key0 = HEX_INPUT_KEY_A;
		else if (Inputs::keyBoardMode == KeyBoardMode::INPUT_AZERTY)
			key0 = HEX_INPUT_KEY_Q;

		break;

	case DirectionalKey::INPUT_DOWN:
		if (Inputs::keyBoardMode == KeyBoardMode::INPUT_QWERTY)
			key0 = HEX_INPUT_KEY_S;
		else if (Inputs::keyBoardMode == KeyBoardMode::INPUT_AZERTY)
			key0 = HEX_INPUT_KEY_S;

		break;
	}

	return glfwGetKey((GLFWwindow*)Context::window, key0) == GLFW_PRESS;
}
