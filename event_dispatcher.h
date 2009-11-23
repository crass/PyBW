#include <string>

#include <Python.h>

class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();

	void onStart();
	void onEnd();
	void onFrame();
	void onSendText(std::string text);

private:
	PyObject* event_handler;
	void LoadEventHandler();
};