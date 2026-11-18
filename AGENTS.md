# AGENTS.md

Working guidance for AI coding agents and developers in the `QuasarApp/QtSDL` repository.

## Description

QtSDL is a small Qt library that bridges raw SDL3 events into Qt's event
loop: `SDLEventManager` (a `QThread` with its own event loop) continuously
polls SDL and wraps each event into a `QSDLEvent` (or a specialized derived
class — gamepad axis/button/added/sensor/touchpad) posted to the Qt main
queue, and tracks gamepad connect/disconnect lifecycle. This makes SDL
input (keyboard, mouse, game controllers) safe to use inside Qt GUI
applications.

- **Language:** C++23 + Qt (Core)
- **Build system:** CMake ≥ 3.19 (typically with Ninja)
- **License:** LGPLv3

### Repository layout

| Path | Contents |
|---|---|
| `src/QtSDL` | the `QtSDL` library (`SDLEventManager` + event classes) |
| `src/testcore` | shared test helpers (used by the example app) |
| `tests/` | Qt Test suite (`QtSDL_tests`, `testcore`-based) |
| `submodules/CMake` | the QuasarApp CMake layer (`QuasarApp/CMake` submodule) |
| `submodules/SDL` | vendored SDL3 (built only with `QTSDL_DEPENDS=ON`) |

### Architecture

- The library links `SDL3::SDL3` (system SDL3, or the vendored submodule
  when `QTSDL_DEPENDS=ON`).
- The QuasarApp CMake layer (`initAll()`) provides the `test` /
  `testQtSDL` / `deploy` / `doc` targets.

## Developing process

### Toolchain

| Tool | Version / notes |
|---|---|
| CMake | ≥ 3.19 |
| Compiler | C++23 required (`CMAKE_CXX_STANDARD 23`) |
| Qt | 6.10 (CI installs 6.10.3), modules: Core, Test |
| SDL3 | 3.3.2 — system install (prefix on `CMAKE_PREFIX_PATH`) or `QTSDL_DEPENDS=ON` (vendored) |
| Ninja | preferred generator |
| CQtDeployer | `cqtdeployer` on `PATH` — required by the `deploy`/`testQtSDL` targets |

### Build

Step by step.

**1. One-time toolchain setup.** Qt 6.10.3 via aqtinstall
(`aqt install-qt linux desktop 6.10.3 gcc_64 -O /opt/Qt`) plus CMake ≥ 3.19,
Ninja and SDL3 (e.g. installed to `/opt/sdl3`, or use `QTSDL_DEPENDS=ON` to
build the vendored SDL submodule).

**2. Get the sources.** Submodules are mandatory (recursive: `CMake`
layer, vendored `SDL`):

```sh
git clone --recurse-submodules https://github.com/QuasarApp/QtSDL.git
# or, for an existing clone:
git submodule update --init --recursive
```

**3. Configure.** (With a system SDL3: put both prefixes on
`CMAKE_PREFIX_PATH` — a `;`-separated list, quoted; alternatively
`-DQTSDL_DEPENDS=ON`.)

```sh
cmake -B build -G Ninja \
  -DCMAKE_PREFIX_PATH="/opt/Qt/6.10.3/gcc_64;/opt/sdl3" \
  -DBUILD_SHARED_LIBS=ON \
  -DCMAKE_BUILD_TYPE=Debug \
  -DQTSDL_TESTS=ON
```

**4. Build.**

```sh
cmake --build build --parallel 16
```

**5. Find the result.** The suite executable lands in its per-target build
dir (`build/tests/QtSDL_tests`); the deliverable is the `QtSDL` library,
plus the example app (built with `QTSDL_EXAMPLE=ON`).

CMake options:

- `QTSDL_TESTS` — build the test suite (default `ON`)
- `QTSDL_EXAMPLE` — build the example app (default `ON`)
- `QTSDL_DEPENDS` — build SDL3 from the vendored submodule (default `OFF`)

### Branching, labels and pull requests (workflow for AI agents)

- Work is issue-driven: one GitHub issue → one branch named
  `task_<issue-number>`, branched **strictly from `main`** — never from
  another task branch.
- Commit messages: short imperative subject + issue reference, e.g.
  `fix: <summary> (issue #<issue>)`, `docs: <summary> (issue #<issue>)`.
- Keep the build and lint green; a red CI blocks the merge.

**The exact commands.**

```sh
# 1. every task starts from a freshly fetched main
git fetch origin
git checkout -b task_<issue> origin/main

# 2. label the issue while working. Workflow labels in this repo:
#    question, help wanted, high/medium/low priority
gh issue edit <issue> --add-label in-progress

# 3. post the initial checklist as a comment; afterwards update that same
#    comment in place, never re-post it
gh issue comment <issue> --body-file /tmp/checklist.md
gh issue comment <issue> --edit-last --body-file /tmp/checklist.md

# 4. push and open the PR — see "Creating the pull request" below
git push -u origin task_<issue>
gh pr create --base main --head task_<issue> \
  --title "<type>: <short imperative summary> (issue #<issue>)" \
  --body-file /tmp/pr_body.md

# 5. the issue goes to waiting-for-review; watch CI from the CLI
gh issue edit <issue> --remove-label in-progress --add-label waiting-for-review
gh pr checks <number>
```

This repo does not define the `in-progress` / `waiting-for-review` labels
yet — create them before first use:
`gh label create in-progress --color '0e8a16'`,
`gh label create waiting-for-review --color 'fbca04'`.

**Status messages — what to post and when.** An agent must keep a
human-readable trail on the issue (and on the PR once it exists). Every
message is a GitHub comment with a `##` heading; the checklist comment is
updated in place (`--edit-last`), never duplicated.

| Stage | Label(s) | Comment template |
|---|---|---|
| Start | `in-progress` | `## Task issue_XXX: <title> — initial checklist (branch task_XXX from main)` — one `- [ ]` line per sub-task |
| Each step done | — | edit the checklist comment: mark the line `- [x]` + one short evidence note (command run, result) |
| Blocked / needs input | `blocked` / `question` | `## Blocked — task_XXX` — what is blocking and exactly what is needed to continue |
| PR opened | `waiting-for-review` | `## Progress — task_XXX` — all lines `- [x]` + `**PR: <url>**` + one-line verification summary |
| Review changes requested | `waiting-for-review` | `## Review-fix cycle — PR #NNN — update` — one `- [x]` line per review point, each with the evidence |
| CI red on the PR | `in-progress` | `## CI failure — PR #NNN` — failing check, cause, fix plan; push the fix, then update the comment |

**Creating the pull request.** An agent has no browser and cannot create a
pull request from the GitHub web UI — it must use the `gh` CLI (a token with
the `repo` scope; in this organisation the agent runs as `QuasarAppCI`):

```sh
gh pr create \
  --base main \
  --head task_<issue> \
  --title "<type>: <short imperative summary> (issue #<issue>)" \
  --body-file /tmp/pr_body.md
```

- The body carries what changed and the verification actually performed
  (commands + their real output); `(issue #<n>)` in the title links the PR
  to the issue. Use `--draft` while still iterating.
- A pull request exists only when `gh pr create` prints its URL. Confirm
  with `gh pr view <number> --json number,url,mergeable` before reporting
  "PR created" — never post that status on faith.
- If work is blocked, keep the PR open, set the issue label to `blocked` and
  post the status message above.

### Documentation rules

- The README documents the supported SDL event types — keep that list in
  sync with the event classes in `src/QtSDL`.
- New event wrappers ship **with** a unit test — never in a follow-up ticket.

## Testing process

### Test infrastructure

Qt Test suite in `tests/` (`tstMain.cpp` + `tests/units/`): the executable
`QtSDL_tests` links `Qt6::Test` and `QtSDL`; built with `QTSDL_TESTS=ON`.
The QuasarApp CMake layer registers `testQtSDL` (deploy via cqtdeployer +
execute) under the `test` aggregate.

### Running the tests from CMake

```sh
cmake -B build -G Ninja -DCMAKE_PREFIX_PATH="/opt/Qt/6.10.3/gcc_64;/opt/sdl3" \
  -DCMAKE_BUILD_TYPE=Debug -DQTSDL_TESTS=ON
cmake --build build --parallel 16
./build/tests/QtSDL_tests
```

### Smoke tests — the most important testing step

The smoke test is: configure + build + run `QtSDL_tests` headless (Qt Test
runs in a `QCoreApplication`, no display needed) in a Debug build, all
units passing. It is the fastest proof that the SDL→Qt event bridge still
works, and it is the gate before any Games/Ecliptica change that touches
input. A red suite blocks the merge.