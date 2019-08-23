#ifndef EVENTS_H
#define EVENTS_H

#pragma once

#include <functional>
#include <algorithm>
#include <memory>
#include <vector>

namespace Sphinx
{
	namespace Forms
	{
		// Represents the method that will handle an event data.
		template <typename TEventArgs>
		class EventHandler
		{
		public:
			EventHandler()
			{
			}

			EventHandler(const EventHandler& other)
			{
				m_ptr = other.m_ptr;
			}

			EventHandler& operator= (const EventHandler& other)
			{
				m_ptr = other.m_ptr;
				return *this;
			}

			template <typename TObject>
			EventHandler(TObject* obj, void (TObject::*fn)(TEventArgs))
			{
				m_ptr.reset(new std::function<void(TEventArgs)>(std::bind(fn, obj, std::placeholders::_1)));
			}

			void operator () (TEventArgs e)
			{
				if (m_ptr.get()) { (*m_ptr)(e); }
			}

			bool operator == (const EventHandler& other)
			{
				return m_ptr == other.m_ptr;
			}

		private:
			std::shared_ptr<std::function<void(TEventArgs)>> m_ptr;
		};

		// Represents a collection of Sphinx::Forms::EventHandler objects.
		template <typename TEventArgs>
		class IEvent
		{
		public:
			IEvent()
			{
			}

			void operator += (const EventHandler<TEventArgs>& handler)
			{
				m_vec.push_back(handler);
			}

			void operator -= (const EventHandler<TEventArgs>& handler)
			{
				m_vec.erase(std::remove(m_vec.begin(), m_vec.end(), handler), m_vec.end());
			}

			void operator () (TEventArgs e)
			{
				for (auto& f : m_vec) { f(e); }
			}

		private:
			IEvent(const IEvent&);
			IEvent& operator = (const IEvent&);

			std::vector<EventHandler<TEventArgs>> m_vec;
		};
	}
}

#endif