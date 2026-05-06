#include <vector>
#include "is_sorted.h"
#include "randfiller.h"
#include "algoritmi_ordinamento.h"

int main(void) {
	randfiller rf;
	for (int k = 1; k <= 100; k++) {
		std::vector<int> int_v(k+2);
		rf.fill(int_v, -40, 40);
		quick_sort(int_v, 0, size(int_v)-1);
		int x = is_sorted(int_v);
		if (x == 0) {
			return EXIT_FAILURE;
		}	
	}
	std::vector<std::string> str_v = {"Italia", "Francia", "Spagna", "Germania", "Austria", "Ungheria","Belgio", "Estonia", "Lettonia", "Lituania"};
	quick_sort(str_v, 0, size(str_v)-1); 
	if (! is_sorted(str_v)) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}