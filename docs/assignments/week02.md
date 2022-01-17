# 2. Project management
## Setup tools
I am using Fedora Linux workstation so many of needed tools were easily available from the distribution package management. Also I have used many of the needed tools earlier so those were already installed.

### Git
Tool was already installed. I have used it a lot.

### GitHub
GitHub was already in use and configured. No need to to anything special. I decided to use it instead of GitLab due to that reason.

### GitHub Pages
Used to host this WWW-site. It is easy to maintain that document just by pulling tree to GitHub using Git. Pages needed to be enabled from GitHub settings.

### MkDocs
First I thought I will maintain static HTML pages by hand. After I looked some videos, recommended MkDocs starts feeling more handy so I decided to give it a try. Also there was Material theme based existing template for the course. Installation was pretty straightforward from the package manager: *sudo dnf install mkdocs-material*. It will install both theme and documentation tool as a dependency. After that I manually copied course template files to my local working Git tree and tested it with command *mkdocs serve*. Worked, pretty simple.

### Graph-Easy
Makes those simple diagrams used.

*echo "[sensor 1], [sensor 2], [sensor N] -> [logic] <-> [radio] [power] -> [logic]" | graph-easy --as_dot | dot -Tpng -o weather_station_graph.png*

Gives you graph:

![](../images/weather_station_graph.png)
