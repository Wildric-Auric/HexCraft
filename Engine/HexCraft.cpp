#include "Context.h"
#include "log.h"

int main() {

	if (!Context::Init())
		return 0;

	while (!Context::shouldTerminate) {
		 Context::Clear();
		 Context::Update();
	}

	Context::Destroy();
}