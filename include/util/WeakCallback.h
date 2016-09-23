#ifndef UTIL_WEAKCALLBACK_H_
#define UTIL_WEAKCALLBACK_H_

#include <functional>
#include <memory>

namespace nc
{
	template<typename CLASS, typename... ARGS>
	class WeakCallback
	{
	public:

		WeakCallback(const std::weak_ptr<CLASS>& object,
			const std::function<void(CLASS*, ARGS...)>& function) :
				object_(object),
				function_(function)
		{}

		void operator()(ARGS&&... args) const
		{
			std::shared_ptr<CLASS> ptr(object_.lock());

			if(ptr)
			{
				function_(ptr.get(), std::forward<ARGS>(args)...);
			}
		}

	private:

		std::weak_ptr<CLASS> object_;

		std::function<void(CLASS*, ARGS)> function_;
	};

	template<typename CLASS, typename... ARGS>
	WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS>& object,
		void (CLASS::*function)(ARGS...))
	{
		return WeakCallback<CLASS, ARGS...>(object, function);
	}

	template<typename CLASS, typename... ARGS>
	WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS>& object,
		void (CLASS::*function)(ARGS...) const)
	{
		return WeakCallback<CLASS, ARGS...>(object, function);
	}

	// template<typename CLASS>
	// class WeakCallback
	// {
	// public:

	// 	WeakCallback(const boost::weak_ptr<CLASS>& object,
	// 		const boost::function<void(CLASS*)>& function) :
	// 			object_(object), function_(function)
	// 	{}

	// 	void operator()() const
	// 	{
	// 		boost::shared_ptr<CLASS> ptr(object_.lock);

	// 		if(ptr)
	// 		{
	// 			function_(ptr.get());
	// 		}
	// 	}

	// private:

	// 	boost::weak_ptr<CLASS> object_;

	// 	boost::function<void(CLASS*)> function_;
	// };

	// template<typename CLASS>
	// WeakCallback<CLASS> makeWeakCallback(const boost::shared_ptr,
	// 	void (CLASS::*function)())
	// {
	// 	return WeakCallback<CLASS>(obejct, function);
	// }

	// template<typename CLASS>
	// WeakCallback<CLASS> makeWeakCallback(const boost::shared_ptr<CLASS>& object,
	// 	void (CLASS::*function)() const)
	// {
	// 	return WeakCallback<CLASS>(object, function);
	// }

}

#endif