PIO ?= pio

.PHONY: help check test coverage smoke smoke-uno smoke-r4-minima webclient webclient-uno webclient-r4-minima tcp_echo tcp_echo-uno tcp_echo-r4-minima poll_demo poll_demo-uno poll_demo-r4-minima seed-secrets clean release-prep release-tag

help: ## Show available targets
	@grep -E '^[a-zA-Z_%-]+:.*##' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*## "}; {printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}'

check: ## Static analysis (cppcheck if available)
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction src/; \
	else \
		echo "cppcheck not found, skipping"; \
	fi

test: ## Run host unit tests
	$(PIO) test -e native

coverage: test ## Coverage report (gcovr -> Coveralls JSON)
	gcovr --root . --filter 'src/' \
	    --exclude-throw-branches --exclude-unreachable-branches \
	    --print-summary --coveralls gcovr-coveralls.json

seed-secrets: ## Seed secrets.h for all examples from templates if missing
	@cp -n examples/smoke/include/secrets.h.example examples/smoke/include/secrets.h 2>/dev/null || true
	@cp -n examples/webclient/include/secrets.h.example examples/webclient/include/secrets.h 2>/dev/null || true
	@cp -n examples/tcp_echo/include/secrets.h.example examples/tcp_echo/include/secrets.h 2>/dev/null || true
	@cp -n examples/poll_demo/include/secrets.h.example examples/poll_demo/include/secrets.h 2>/dev/null || true

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

tcp_echo: tcp_echo-uno tcp_echo-r4-minima ## Build tcp_echo example for all boards

tcp_echo-uno: seed-secrets ## Build tcp_echo for Arduino UNO R3 (AVR) + CC3000
	$(PIO) run -d examples/tcp_echo -e uno

tcp_echo-r4-minima: seed-secrets ## Build tcp_echo for Arduino UNO R4 Minima + CC3000
	$(PIO) run -d examples/tcp_echo -e r4_minima

poll_demo: poll_demo-uno poll_demo-r4-minima ## Build poll_demo example for all boards

poll_demo-uno: seed-secrets ## Build poll_demo for Arduino UNO R3 (AVR) + CC3000
	$(PIO) run -d examples/poll_demo -e uno

poll_demo-r4-minima: seed-secrets ## Build poll_demo for Arduino UNO R4 Minima + CC3000
	$(PIO) run -d examples/poll_demo -e r4_minima

clean: ## Clean PIO build artifacts
	$(PIO) run -d examples/smoke -t clean
	$(PIO) run -d examples/webclient -t clean
	$(PIO) run -d examples/tcp_echo -t clean
	$(PIO) run -d examples/poll_demo -t clean

# --- Release ---------------------------------------------------------------
# Two-step because branch protection requires PR-mediated merges.
#
#   make release-prep VERSION=X.Y.Z   -> branch + bump library.properties + PR
#   (review + merge PR via gh / GitHub UI)
#   make release-tag  VERSION=X.Y.Z   -> tag main + push tag (release.yml fires)
#
# VERSION must be semver (X.Y.Z, no leading v).

release-prep: ## Open a version-bump PR (VERSION=X.Y.Z required)
	@test -n "$(VERSION)" || { echo "error: VERSION required (e.g. make release-prep VERSION=0.2.0)"; exit 1; }
	@echo "$(VERSION)" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+$$' || { echo "error: VERSION must be semver X.Y.Z"; exit 1; }
	@test "$$(git rev-parse --abbrev-ref HEAD)" = "main" || { echo "error: must be on main"; exit 1; }
	git pull
	git checkout -b jae/bump-version-$(VERSION)
	sed -i '' -e 's/^version=.*/version=$(VERSION)/' library.properties
	git add library.properties
	git commit -S -m "chore: bump version to $(VERSION)"
	git push -u origin jae/bump-version-$(VERSION)
	gh create-pull-request-auto

release-tag: ## Tag main + push tag (VERSION=X.Y.Z required, after PR merged)
	@test -n "$(VERSION)" || { echo "error: VERSION required (e.g. make release-tag VERSION=0.2.0)"; exit 1; }
	@echo "$(VERSION)" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+$$' || { echo "error: VERSION must be semver X.Y.Z"; exit 1; }
	@test "$$(git rev-parse --abbrev-ref HEAD)" = "main" || { echo "error: must be on main"; exit 1; }
	git pull
	@grep -q '^version=$(VERSION)$$' library.properties || { echo "error: library.properties version != $(VERSION); merge release-prep PR first"; exit 1; }
	@git rev-parse v$(VERSION) >/dev/null 2>&1 && { echo "error: tag v$(VERSION) already exists"; exit 1; } || true
	git tag -s -a v$(VERSION) -m "chore: v$(VERSION) tag"
	git push origin v$(VERSION)
