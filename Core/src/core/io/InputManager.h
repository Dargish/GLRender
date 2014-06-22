#pragma once
#include "../fwd.h"
#include <SFML/Window.hpp>
#include <vector>
#include <map>

namespace io
{
	struct Axis
	{
		enum Enum
		{
			X = 0,
			Y
		};
	};

	class InputAssignment
	{
	public:
		virtual bool isDown() const;
		virtual bool wasDown() const;
		virtual int iValue() const;
		virtual int iDelta() const;
		virtual float fValue() const;
		virtual float fDelta() const;
	};

	class KeyInputAssignment : public InputAssignment
	{
	public:
		KeyInputAssignment(sf::Keyboard::Key key);
		virtual bool isDown() const;
		virtual bool wasDown() const;

		sf::Keyboard::Key key() const;
	private:
		const sf::Keyboard::Key m_key;
		bool m_keyPressed, m_oldKeyPressed;
	};

	class MouseButtonInputAssignment : public InputAssignment
	{
	public:
		MouseButtonInputAssignment(sf::Mouse::Button button);
		virtual bool isDown() const;
		virtual bool wasDown() const;

		sf::Mouse::Button button() const;
	private:
		const sf::Mouse::Button m_button;
		bool m_buttonPressed, m_oldButtonPressed;
	};

	class MouseAxisInputAssignment : public InputAssignment
	{
	public:
		MouseAxisInputAssignment(Axis::Enum axis);
		virtual int iValue() const;
		virtual int iDelta() const;

		Axis::Enum axis() const;
	private:
		const Axis::Enum m_axis;
		int m_value, m_oldValue;
	};

	class MappedInput : public InputAssignment
	{
	public:
		MappedInput(const std::string& name);
		MappedInput(const std::string& name, const InputAssignment_Ptr& input);
		MappedInput(const std::string& name, const std::vector<InputAssignment_Ptr>& inputs);

		void addAssignment(const InputAssignment_Ptr& input);

		const std::string& name() const;
		virtual bool isDown() const;
		virtual bool wasDown() const;
		virtual int iValue() const;
		virtual int iDelta() const;
		virtual float fValue() const;
		virtual float fDelta() const;

	private:
		std::string m_name;
		std::vector<InputAssignment_Ptr> m_inputs;
	};

	class KeyboardState
	{
	public:
		void update();
		void operator=(const KeyboardState& other);
		bool isKeyPressed(sf::Keyboard::Key key) const;

	private:
		std::map<sf::Keyboard::Key, bool> m_state;
	};

	class MouseState
	{
	public:
		void update();
		void operator=(const MouseState& other);
		bool isButtonPressed(sf::Mouse::Button button) const;
		int x() const;
		int y() const;
		void setX(int x);
		void setY(int y);

	private:
		std::map<sf::Mouse::Button, bool> m_buttonState;
		int m_x, m_y;
	};

	class InputState
	{
	public:
		KeyboardState keyboard;
		MouseState mouse;
		InputState_Ptr previous;
	};

	class InputManager
	{
	public:
		static InputManager_Ptr Instance();
		~InputManager();

		const InputState_Ptr& state() const;
		void setMouseLocked(bool locked);
		void update();
		void addInput(const std::string assignmentName, sf::Keyboard::Key key);
		void addInput(const std::string assignmentName, sf::Mouse::Button button);
		void addInput(const std::string assignmentName, Axis::Enum axis);
		void addInputAssignment(const std::string& assignmentName, const InputAssignment_Ptr& assignment);
		void setInput(const std::string assignmentName, sf::Keyboard::Key key);
		void setInput(const std::string assignmentName, sf::Mouse::Button button);
		void setInput(const std::string assignmentName, Axis::Enum axis);
		void setMappedInput(const MappedInput_Ptr& mappedInput);
		bool hasMappedInput(const std::string& assignmentName) const;
		bool isDown(const std::string& assignmentName) const;
		bool wasDown(const std::string& assignmentName) const;
		int iValue(const std::string& assignmentName) const;
		int iDelta(const std::string& assignmentName) const;
		float fValue(const std::string& assignmentName) const;
		float fDelta(const std::string& assignmentName) const;

		static const InputState_Ptr& State();
		static void SetMouseLocked(bool locked);
		static void Update();
		static void AddInput(const std::string assignmentName, sf::Keyboard::Key key);
		static void AddInput(const std::string assignmentName, sf::Mouse::Button button);
		static void AddInput(const std::string assignmentName, Axis::Enum axis);
		static void AddInputAssignment(const std::string& assignmentName, const InputAssignment_Ptr& assignment);
		static void SetInput(const std::string assignmentName, sf::Keyboard::Key key);
		static void SetInput(const std::string assignmentName, sf::Mouse::Button button);
		static void SetInput(const std::string assignmentName, Axis::Enum axis);
		static void SetMappedInput(const MappedInput_Ptr& mappedInput);
		static bool HasMappedInput(const std::string& assignmentName);
		static bool IsDown(const std::string& assignmentName);
		static bool WasDown(const std::string& assignmentName);
		static int IValue(const std::string& assignmentName);
		static int IDelta(const std::string& assignmentName);
		static float FValue(const std::string& assignmentName);
		static float FDelta(const std::string& assignmentName);

	private:
		InputManager();

		static InputManager_Ptr s_instance;
		std::map<std::string, MappedInput_Ptr> m_mappedInputs;

		bool m_lockMouse;
		InputState_Ptr m_inputState;
	};
}

