#ifndef		__OBJECT_DELETER_HPP__
#define		__OBJECT_DELETER_HPP__

template <typename T>
class ObjectDeleter
{
	private:
		ObjectDeleter() {}
		T	mpPointer;

	public:
		ObjectDeleter( T rpPointer ) : mpPointer( rpPointer ) {}
		virtual ~ObjectDeleter() { delete mpPointer; }
};

#endif
