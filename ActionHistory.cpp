#include "ActionHistory.h"

#include "EditorAction.h"
#include "EngineBackend.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;

ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::initialize()
{
	sharedInstance = new ActionHistory;
}

void ActionHistory::destroy()
{
	delete sharedInstance;
}

void ActionHistory::recordAction(AGameObject* gameObject)
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR)
	{
		EditorAction* editorAction = new EditorAction(gameObject);
		this->actionsPerformed.push(editorAction);

		std::cout << "Stored action " << gameObject->getName() << std::endl;
	}
}

bool ActionHistory::hasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
	return !this->actionsCancelled.empty();
}

EditorAction* ActionHistory::undoAction()
{
	if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR)
	{
		std::cout << "Cannot perform any undo during play." << std::endl;
		return NULL;
	}

	if (this->hasRemainingUndoActions())
	{
		EditorAction* action = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsCancelled.push(action);
		return action;
	}
	else
	{
		std::cout << "No more actions remaining." << std::endl;
		return NULL;
	}
}

EditorAction* ActionHistory::redoAction()
{
	if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR)
	{
		std::cout << "Cannot perform any redo during play." << std::endl;
		return NULL;
	}

	if (this->hasRemainingRedoActions())
	{
		EditorAction* action = this->actionsCancelled.top();
		this->actionsCancelled.pop();
		this->actionsPerformed.push(action);
		return action;
	}
	else
	{
		std::cout << "No more actions remaining." << std::endl;
		return NULL;
	}
}

void ActionHistory::clear()
{
	this->actionsPerformed.empty();
	this->actionsCancelled.empty();
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}
