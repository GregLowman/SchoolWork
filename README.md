# SchoolWork
A collection of coursework completed throughout my CS degree, organized by class and assignment order. Each project includes well-documented code and a README outlining its scope and objectives. Languages &amp; Technologies: C, C++, HTML, CSS, JavaScript, Handlebars
---

## CSCI 2270 — Data Structures (C++)

Twelve projects working through all the major data structures — not just implementing them, but building things that actually use them. Early assignments covered sorting stock data and working with dynamic arrays, then a music playlist project that ran for three iterations — starting as a singly linked list, then growing to include Floyd's cycle detection, range deletion, and two-list merging.

From there it was stacks and queues through a pancake shop simulation, which was more interesting than it sounds — a linked-list queue for orders and an array-backed stack handling the cash register. Two back-to-back BST projects built out a movie collection, the second adding node deletion across all three cases, left rotation, and lowest common ancestor.

The graph projects were probably my favorite — a LinkedIn-style network using BFS for connection traversal and k-th order suggestions, and a dungeon crawler using DFS with contamination zone logic. The capstone tied everything together: a hash table, priority queue, and graph combined into a dungeon item management system.

---

## CSCI 2400 — Computer Systems (C/C++)

Six low-level labs covering the parts of CS that most higher-level coursework skips over. Starts with bit manipulation puzzles — implementing standard integer and float operations using only eight bitwise operators, no conditionals allowed. From there, a binary bomb lab defused entirely through GDB and objdump disassembly, with annotated analysis files for each phase.

The remaining labs cover code injection and return-oriented programming exploits against intentionally vulnerable binaries, optimizing a five-loop image convolution pipeline for throughput, a complete Unix shell with foreground/background job control and signal handling for SIGCHLD, SIGINT, and SIGTSTP, and a dynamic memory allocator implementing malloc, free, and realloc with an explicit free list and boundary-tag coalescing.

---

## CSCI 3308 — Software Development Methods (Web / Full-Stack)

Seven incremental labs building toward full-stack development, starting from the ground up. The first couple cover environment setup with Docker and Node.js, shell scripting, and Git workflow automation. Then a static portfolio in HTML and CSS, a vanilla JavaScript calendar app with no frameworks, and a PostgreSQL database for movies, actors, genres, and platforms with a full query set.

Things got more interesting with a Node.js and Express REST API server paired with Docker Compose and a Postman collection, then a full-stack web service with session-based authentication, a discovery page pulling from the Ticketmaster API, and server-side Handlebars rendering.

The course closed with a group final project — Daily Dev Mix — a Spotify companion app where users pick an activity "vibe," track their listening session live via the Spotify API, and automatically generate a playlist from that session's data. Built with Node.js, Express, PostgreSQL, and Handlebars, deployed on Railway. That one has its own repo.

---

## Structure

Each folder is named and ordered by course and assignment. Every project has its own README covering the problem, approach, and anything worth noting about the implementation.
