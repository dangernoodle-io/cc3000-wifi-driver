PIO ?= pio

.PHONY: help check smoke smoke-uno smoke-r4-minima webclient webclient-uno webclient-r4-minima seed-secrets clean

help: ## Show available targets
	@grep -E '^[a-zA-Z_%-]+:.*##' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*## "}; {printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}'

check: ## Static analysis (cppcheck if available)
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction src/; \
	else \
		echo "cppcheck not found, skipping"; \
	fi

seed-secrets: ## Seed secrets.h for both examples from templates if missing
	@cp -n examples/smoke/include/secrets.h.example examples/smoke/include/secrets.h 2>/dev/null || true
	@cp -n examples/webclient/include/secrets.h.example examples/webclient/include/secrets.h 2>/dev/null || true

smoke: smoke-uno smoke-r4-minima ## Build smoke example for all boards

smoke-uno: seed-secrets ## Build smoke for Arduino UNO R3 (AVR) + CC3000
	$(PIO) run -d examples/smoke -e uno

smoke-r4-minima: seed-secrets ## Build smoke for Arduino UNO R4 Minima + CC3000
	$(PIO) run -d examples/smoke -e r4_minima

webclient: webclient-uno webclient-r4-minima ## Build webclient example for all boards

webclient-uno: seed-secrets ## Build webclient for Arduino UNO R3 (AVR) + CC3000
	$(PIO) run -d examples/webclient -e uno

webclient-r4-minima: seed-secrets ## Build webclient for Arduino UNO R4 Minima + CC3000
	$(PIO) run -d examples/webclient -e r4_minima

clean: ## Clean PIO build artifacts
	$(PIO) run -d examples/smoke -t clean
	$(PIO) run -d examples/webclient -t clean
