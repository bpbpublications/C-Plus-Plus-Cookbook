module;
import <iostream>;

export module Module10_1_3;

export {  // exports everything withing the block; could be classes, namespaces, functions, etc.
	class Class10_1_3a {
	public:
		void Nothing() {}
	};

	class Class10_1_3b {
	public:
		void Nothing() {}
	};

	namespace NameSpace1 {
		class Class10_1_3d {
		public:
			void Nothing() {}
		};

		class Class10_1_3e {
		public:
			void Nothing() {}
		};
	}

#ifndef _MSC_VER
	// Microsoft compiler not exporting static methods yet
	static void PlainNothing() {}
#endif
}

export namespace NameSpace2 { // declares a namespace, and everything within the block is exported
	class Class10_1_3e {
	public:
		void Nothing() {}
	};

	class Class10_1_3f {
	public:
		void Nothing() {}
	};
}

namespace NameSpace2 {
	class NotExported {
	public:
		void Nothing() {}
	};
}

#ifndef _MSC_VER
// Microsoft compiler not exporting static methods yet
export static void VeryPlainNothing() {} // function is exported
#endif

static void AlsoPlainButNotExported() {}
