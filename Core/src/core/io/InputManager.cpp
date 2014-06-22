#include "InputManager.h"
#include "../Window.h"

namespace io
{
	bool InputAssignment::isDown() const
	{
		return false;
	}

	bool InputAssignment::wasDown() const
	{
		return false;
	}

	int InputAssignment::iValue() const
	{
		return int(isDown());
	}

	int InputAssignment::iDelta() const
	{
		return int(isDown());
	}

	float InputAssignment::fValue() const
	{
		return float(iValue());
	}

	float InputAssignment::fDelta() const
	{
		return float(iDelta());
	}


	KeyInputAssignment::KeyInputAssignment(sf::Keyboard::Key key) : m_key(key)
	{

	}

	bool KeyInputAssignment::isDown() const
	{
		return InputManager::State()->keyboard.isKeyPressed(m_key);
	}

	bool KeyInputAssignment::wasDown() const
	{
		return InputManager::State()->previous->keyboard.isKeyPressed(m_key);
	}

	sf::Keyboard::Key KeyInputAssignment::key() const
	{
		return m_key;
	}


	MouseButtonInputAssignment::MouseButtonInputAssignment(sf::Mouse::Button button) : m_button(button)
	{

	}

	bool MouseButtonInputAssignment::isDown() const
	{
		return InputManager::State()->mouse.isButtonPressed(m_button);
	}

	bool MouseButtonInputAssignment::wasDown() const
	{
		return InputManager::State()->previous->mouse.isButtonPressed(m_button);
	}

	sf::Mouse::Button MouseButtonInputAssignment::button() const
	{
		return m_button;
	}


	MouseAxisInputAssignment::MouseAxisInputAssignment(Axis::Enum axis) : m_axis(axis)
	{

	}

	int MouseAxisInputAssignment::iValue() const
	{
		if (m_axis == Axis::X)
		{
			return InputManager::State()->mouse.x();
		}
		if (m_axis == Axis::Y)
		{
			return InputManager::State()->mouse.y();
		}
		return 0;
	}

	int MouseAxisInputAssignment::iDelta() const
	{
		if (m_axis == Axis::X)
		{
			InputState_Ptr inputState = InputManager::State();
			return inputState->mouse.x() - inputState->previous->mouse.x();
		}
		if (m_axis == Axis::Y)
		{
			InputState_Ptr inputState = InputManager::State();
			return inputState->mouse.y() - inputState->previous->mouse.y();
		}
		return 0;
	}

	Axis::Enum MouseAxisInputAssignment::axis() const
	{
		return m_axis;
	}


	MappedInput::MappedInput(const std::string& name) : m_name(name)
	{

	}

	MappedInput::MappedInput(const std::string& name, const InputAssignment_Ptr& input) : m_name(name)
	{
		m_inputs.push_back(input);
	}

	MappedInput::MappedInput(const std::string& name, const std::vector<InputAssignment_Ptr>& inputs) : m_name(name), m_inputs(inputs)
	{

	}

	void MappedInput::addAssignment(const InputAssignment_Ptr& input)
	{
		m_inputs.push_back(input);
	}

	const std::string& MappedInput::name() const
	{
		return m_name;
	}

	bool MappedInput::isDown() const
	{
		std::vector<InputAssignment_Ptr>::const_iterator it = m_inputs.begin();
		for (; it != m_inputs.end(); ++it)
		{
			if ((*it)->isDown())
			{
				return true;
			}
		}
		return false;
	}

	bool MappedInput::wasDown() const
	{
		std::vector<InputAssignment_Ptr>::const_iterator it = m_inputs.begin();
		for (; it != m_inputs.end(); ++it)
		{
			if ((*it)->wasDown())
			{
				return true;
			}
		}
		return false;
	}

	int MappedInput::iValue() const
	{
		if (!m_inputs.empty())
		{
			return m_inputs.front()->iValue();
		}
		return 0;
	}

	int MappedInput::iDelta() const
	{
		if (!m_inputs.empty())
		{
			return m_inputs.front()->iDelta();
		}
		return 0;
	}

	float MappedInput::fValue() const
	{
		if (!m_inputs.empty())
		{
			return m_inputs.front()->fValue();
		}
		return 0.0f;
	}

	float MappedInput::fDelta() const
	{
		if (!m_inputs.empty())
		{
			return m_inputs.front()->fDelta();
		}
		return 0.0f;
	}


	void KeyboardState::update()
	{
		for (sf::Keyboard::Key key = sf::Keyboard::Key(0); key < sf::Keyboard::Key::KeyCount; key = sf::Keyboard::Key(int(key) + 1))
		{
			m_state[key] = sf::Keyboard::isKeyPressed(key);
		}
	}

	void KeyboardState::operator=(const KeyboardState& other)
	{
		for (sf::Keyboard::Key key = sf::Keyboard::Key(0); key < sf::Keyboard::Key::KeyCount; key = sf::Keyboard::Key(int(key) + 1))
		{
			std::map<sf::Keyboard::Key, bool>::const_iterator it = other.m_state.find(key);
			if (it != other.m_state.end())
			{
				m_state[key] = it->second;
			}
			else
			{
				m_state[key] = false;
			}
		}
	}

	bool KeyboardState::isKeyPressed(sf::Keyboard::Key key) const
	{
		std::map<sf::Keyboard::Key, bool>::const_iterator it = m_state.find(key);
		if (it != m_state.end())
		{
			return it->second;
		}
		return false;
	}


	void MouseState::update()
	{
		for (sf::Mouse::Button btn = sf::Mouse::Button(0); btn < sf::Mouse::Button::ButtonCount; btn = sf::Mouse::Button(int(btn) + 1))
		{
			m_buttonState[btn] = sf::Mouse::isButtonPressed(btn);
		}
		m_x = sf::Mouse::getPosition().x;
		m_y = sf::Mouse::getPosition().y;
	}

	void MouseState::operator=(const MouseState& other)
	{
		for (sf::Mouse::Button btn = sf::Mouse::Button(0); btn < sf::Mouse::Button::ButtonCount; btn = sf::Mouse::Button(int(btn) + 1))
		{
			std::map<sf::Mouse::Button, bool>::const_iterator it = other.m_buttonState.find(btn);
			if (it != other.m_buttonState.end())
			{
				m_buttonState[btn] = it->second;
			}
			else
			{
				m_buttonState[btn] = false;
			}
		}
		m_x = other.x();
		m_y = other.y();
	}

	bool MouseState::isButtonPressed(sf::Mouse::Button button) const
	{
		std::map<sf::Mouse::Button, bool>::const_iterator it = m_buttonState.find(button);
		if (it != m_buttonState.end())
		{
			return it->second;
		}
		return false;
	}

	int MouseState::x() const
	{
		return m_x;
	}

	int MouseState::y() const
	{
		return m_y;
	}

	void MouseState::setX(int x)
	{
		m_x = x;
	}

	void MouseState::setY(int y)
	{
		m_y = y;
	}


	InputManager_Ptr InputManager::Instance()
	{
		if (!s_instance.get())
		{
			s_instance.reset(new InputManager);
		}
		return s_instance;
	}

	InputManager_Ptr InputManager::s_instance;

	InputManager::InputManager() : m_lockMouse(false), m_inputState(new InputState)
	{
		m_inputState->previous.reset(new InputState);
	}

	InputManager::~InputManager()
	{

	}

	const InputState_Ptr& InputManager::state() const
	{
		return m_inputState;
	}

	void InputManager::setMouseLocked(bool lockMouse)
	{
		m_lockMouse = lockMouse;
	}

	void InputManager::update()
	{
		m_inputState->previous->keyboard = m_inputState->keyboard;
		m_inputState->previous->mouse = m_inputState->mouse;
		m_inputState->keyboard.update();
		m_inputState->mouse.update();
		sf::RenderWindow_Ptr window = Window::GetWindow();
		window->setMouseCursorVisible(!m_lockMouse);
		if (m_lockMouse)
		{
			sf::Vector2i pos = window->getPosition();
			sf::Vector2u size = window->getSize();
			pos.x += size.x / 2;
			pos.y += size.y / 2;
			sf::Mouse::setPosition(pos);
			m_inputState->previous->mouse.setX(pos.x);
			m_inputState->previous->mouse.setY(pos.y);
			window->setMouseCursorVisible(false);
		}
	}

	void InputManager::addInput(const std::string assignmentName, sf::Keyboard::Key key)
	{
		KeyInputAssignment_Ptr assignment(new KeyInputAssignment(key));
		addInputAssignment(assignmentName, assignment);
	}

	void InputManager::addInput(const std::string assignmentName, sf::Mouse::Button button)
	{
		MouseButtonInputAssignment_Ptr assignment(new MouseButtonInputAssignment(button));
		addInputAssignment(assignmentName, assignment);
	}

	void InputManager::addInput(const std::string assignmentName, Axis::Enum axis)
	{
		MouseAxisInputAssignment_Ptr assignment(new MouseAxisInputAssignment(axis));
		addInputAssignment(assignmentName, assignment);
	}

	void InputManager::addInputAssignment(const std::string& assignmentName, const InputAssignment_Ptr& assignment)
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it == m_mappedInputs.end())
		{
			MappedInput_Ptr mappedAssignment(new MappedInput(assignmentName, assignment));
			setMappedInput(mappedAssignment);
		}
		else
		{
			it->second->addAssignment(assignment);
		}
	}

	void InputManager::setInput(const std::string assignmentName, sf::Keyboard::Key key)
	{
		KeyInputAssignment_Ptr assignment(new KeyInputAssignment(key));
		MappedInput_Ptr mappedAssignment(new MappedInput(assignmentName, assignment));
		setMappedInput(mappedAssignment);
	}

	void InputManager::setInput(const std::string assignmentName, sf::Mouse::Button button)
	{
		MouseButtonInputAssignment_Ptr assignment(new MouseButtonInputAssignment(button));
		MappedInput_Ptr mappedAssignment(new MappedInput(assignmentName, assignment));
		setMappedInput(mappedAssignment);
	}

	void InputManager::setInput(const std::string assignmentName, Axis::Enum axis)
	{
		MouseAxisInputAssignment_Ptr assignment(new MouseAxisInputAssignment(axis));
		MappedInput_Ptr mappedAssignment(new MappedInput(assignmentName, assignment));
		setMappedInput(mappedAssignment);
	}

	void InputManager::setMappedInput(const MappedInput_Ptr& mappedInput)
	{
		m_mappedInputs[mappedInput->name()] = mappedInput;
	}

	bool InputManager::hasMappedInput(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		return (it != m_mappedInputs.end());
	}

	bool InputManager::isDown(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it != m_mappedInputs.end())
		{
			return (it->second->isDown());
		}
		return false;
	}

	bool InputManager::wasDown(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it != m_mappedInputs.end())
		{
			return (it->second->wasDown());
		}
		return false;
	}

	int InputManager::iValue(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it != m_mappedInputs.end())
		{
			return (it->second->iValue());
		}
		return 0;
	}

	int InputManager::iDelta(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it != m_mappedInputs.end())
		{
			return (it->second->iDelta());
		}
		return 0;
	}

	float InputManager::fValue(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it != m_mappedInputs.end())
		{
			return (it->second->fValue());
		}
		return 0.0f;
	}

	float InputManager::fDelta(const std::string& assignmentName) const
	{
		std::map<std::string, MappedInput_Ptr>::const_iterator it = m_mappedInputs.find(assignmentName);
		if (it != m_mappedInputs.end())
		{
			return (it->second->fDelta());
		}
		return 0.0f;
	}

	const InputState_Ptr& InputManager::State()
	{
		return Instance()->state();
	}

	void InputManager::SetMouseLocked(bool locked)
	{
		Instance()->setMouseLocked(locked);
	}

	void InputManager::Update()
	{
		Instance()->update();
	}

	void InputManager::AddInput(const std::string assignmentName, sf::Keyboard::Key key)
	{
		Instance()->addInput(assignmentName, key);
	}

	void InputManager::AddInput(const std::string assignmentName, sf::Mouse::Button button)
	{
		Instance()->addInput(assignmentName, button);
	}

	void InputManager::AddInput(const std::string assignmentName, Axis::Enum axis)
	{
		Instance()->addInput(assignmentName, axis);
	}

	void InputManager::AddInputAssignment(const std::string& assignmentName, const InputAssignment_Ptr& assignment)
	{
		Instance()->addInputAssignment(assignmentName, assignment);
	}

	void InputManager::SetInput(const std::string assignmentName, sf::Keyboard::Key key)
	{
		Instance()->setInput(assignmentName, key);
	}

	void InputManager::SetInput(const std::string assignmentName, sf::Mouse::Button button)
	{
		Instance()->setInput(assignmentName, button);
	}

	void InputManager::SetInput(const std::string assignmentName, Axis::Enum axis)
	{
		Instance()->setInput(assignmentName, axis);
	}

	void InputManager::SetMappedInput(const MappedInput_Ptr& mappedInput)
	{
		Instance()->setMappedInput(mappedInput);
	}

	bool InputManager::HasMappedInput(const std::string& assignmentName)
	{
		return Instance()->hasMappedInput(assignmentName);
	}

	bool InputManager::IsDown(const std::string& assignmentName)
	{
		return Instance()->isDown(assignmentName);
	}

	bool InputManager::WasDown(const std::string& assignmentName)
	{
		return Instance()->wasDown(assignmentName);
	}

	int InputManager::IValue(const std::string& assignmentName)
	{
		return Instance()->iValue(assignmentName);
	}

	int InputManager::IDelta(const std::string& assignmentName)
	{
		return Instance()->iDelta(assignmentName);
	}

	float InputManager::FValue(const std::string& assignmentName)
	{
		return Instance()->fValue(assignmentName);
	}

	float InputManager::FDelta(const std::string& assignmentName)
	{
		return Instance()->fDelta(assignmentName);
	}
}
