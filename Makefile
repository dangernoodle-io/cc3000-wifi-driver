PIO ?= pio

.PHONY: help check smoke smoke-uno smoke-uno_r4_minima clean

help: ## Show available targets
	@grep -E '^[a-zA-Z_%-]+:.*##' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*## "}; {printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}'

check: ## Static analysis (cppcheck if available)
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction src/; \
	else \
		echo "cppcheck not found, skipping"; \
	fi

smoke: smoke-uno smoke-uno_r4_minima ## Build smoke example for all boards

smoke-uno: ## Build smoke for Arduino UNO R3 (AVR) + CC3000
	$(PIO) run -d examples/smoke -e uno

smoke-uno_r4_minima: ## Build smoke for Arduino UNO R4 Minima + CC3000
	$(PIO) run -d examples/smoke -e uno_r4_minima

clean: ## Clean PIO build artifacts
	$(PIO) run -d examples/smoke -t clean
