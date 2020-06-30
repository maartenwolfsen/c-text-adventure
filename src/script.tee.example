# this is a comment
# [p] = print
# [z {choices}] = choice;
#   Example: [c {a:Label 1;b:Label 2;c:Label 3}]
# [a] = choice type
# [q quotee] = quote
#   Output: "Quotee": q
# [f function] = function
# $varname = variable
#   Example: This is a string from $name
#   Variable name must be set via set function

[p]  ________            ______                      __         
[p] /_  __/ /_  ___     /_  __/________ __   _____  / /__  _____
[p]  / / / __ \/ _ \     / / / ___/ __ `/ | / / _ \/ / _ \/ ___/
[p] / / / / / /  __/    / / / /  / /_/ /| |/ /  __/ /  __/ /    
[p]/_/ /_/ /_/\___/    /_/ /_/   \__,_/ |___/\___/_/\___/_/     
[p]                      A Short Story by Maarten Wolfsen
[p]---- Main Menu -------------------------------------
[z {a:Start Game;b:Quit to Desktop}]
    [a]
        [q Bartender]Hello weary Traveler. You have been on quite the Journey, what is your name?
        [f setName]
        [q Bartender]So $name... I have never seen you before...
        [q Bartender]Where are you from?
        [f setLocation]
        [q Bartender]Ah... $location... From afar I see...
        [q Bartender]Make yourself at home, $name of $location, ask me if you need anything.
        [z {a:Grab a drink and sit at the bar.;b:Grab a drink and sit at a empty table.;c:Grab a drink and sit at a table beside someone.}]
            [a]
                [p]You order a drink and go sit at the bar.
                [p]After a short while, a stranger sits right next to you and orders a beer.
                [p]You notice his hand is torn open and bleeding.
                [q Bartender]How are you going to pay for that beer, stranger?
                [p]It seems that the stranger does not have enough money to pay for the beer.
                [z {a:Pay for his beer.;b:Don't pay for his beer.}]
                    [a]
                        [q Stranger]Thank you Traveler...
                        [end]
                    [b]
                        [q Stranger]What a world we live in...
                        [end]
                
            [b]
                [p]You sit at an empty table...
                [p]Nothing happens and after two hours you leave.
                [end]
            [c]
                [p]You see a man wearing a high hat sitting at a table.
                [p]You decide to sit beside him.
                [q Man with the High Hat]Hello young Traveler, how are you today?
                    [z {a:I'm fine;b:Meh...}]
                        [a]
                            [q Man with the High Hat]Good... Good...
                            [p]You and the Man with the High Hat finish your drinks.
                            [p]You decide to go.
                            [end]
                        [b]
                            [p]The Man with the High Hat doesn't really know what to say.
                            [p]The two of you sit in silence for about five minutes.
                            [p]You decide to leave.
                            [end]
                [end]
    [b]
        [end]