%Benjamin Metz
%{
Attempt 1 at making a chord progression generator that uses the chord
progression map and random number generation
Started January 11th, 2020
Version as of January 12th, 2020
%}
clc; clear all;
%% Big array defining
%{ 
Define each chord with what chords come before and after
array: 28 boxes, each with a space for an
ID, chords before, and chords after
%}
pattern=zeros(25,3,6);

%block 1
pattern(1,1,1)=1; %ID
pattern(1,2,1)=5; %before #1
pattern(1,2,2)=6; %before #2
pattern(1,2,3)=4; %before #3
pattern(1,3,1)=2; %after #1
pattern(1,3,2)=3; %after #2
pattern(1,3,3)=7; %after #3
pattern(1,3,4)=9; %after #4

%block 2
pattern(2,1,1)=2; %ID
pattern(2,2,1)=15; %before #1
pattern(2,2,2)=17; %before #2
pattern(2,2,3)=1; %before #3
pattern(2,2,4)=5; %before #4
pattern(2,2,5)=7; %before #5
pattern(2,3,1)=3; %after #1
pattern(2,3,2)=4; %after #2
pattern(2,3,3)=9; %after #3

%block 3
pattern(3,1,1)=3; %ID
pattern(3,2,1)=1; %before #1
pattern(3,2,2)=2; %before #2
pattern(3,2,3)=10; %before #3
pattern(3,2,4)=11; %before #4
pattern(3,3,1)=9; %after #1
pattern(3,3,2)=5; %after #2
pattern(3,3,3)=4; %after #3

%block 4
pattern(4,1,1)=4; %ID
pattern(4,2,1)=2; %before #1
pattern(4,2,2)=3; %before #2
pattern(4,2,3)=20; %before #3
pattern(4,2,4)=22; %before #4
pattern(4,3,1)=1; %after #1
pattern(4,3,2)=5; %after #2

%block 5
pattern(5,1,1)=5; %ID
pattern(5,2,1)=12; %before #1
pattern(5,2,2)=14; %before #2
pattern(5,2,3)=3; %before #3
pattern(5,2,4)=4; %before #4
pattern(5,3,1)=9; %after #1
pattern(5,3,2)=6; %after #2
pattern(5,3,3)=1; %after #3
pattern(5,3,4)=2; %after #4
pattern(5,3,5)=7; %after #5

%block 6
pattern(6,1,1)=6; %ID
pattern(6,2,1)=5; %before #1
pattern(6,3,1)=1; %after #1

%block 7
pattern(7,1,1)=7; %ID
pattern(7,2,1)=23; %before #1
pattern(7,2,2)=24; %before #2
pattern(7,2,3)=1; %before #3
pattern(7,2,4)=5; %before #4
pattern(7,3,1)=2; %after #1

%block 8
pattern(8,1,1)=8; %ID
pattern(8,2,1)=9; %before #1
pattern(8,3,1)=9; %after #1

%block 9
pattern(9,1,1)=9; %ID
pattern(9,2,1)=19; %before #1
pattern(9,2,2)=3; %before #2
pattern(9,2,3)=5; %before #3
pattern(9,2,4)=2; %before #4
pattern(9,2,5)=25; %before #5
pattern(9,2,6)=8; %before #6

%block 10
pattern(10,1,1)=10; %ID
pattern(10,3,1)=3; %after #1

%block 11
pattern(11,1,1)=11; %ID
pattern(11,3,1)=3; %after #1

%block 12
pattern(12,1,1)=12; %ID
pattern(12,3,1)=5; %after #1

%block 13
pattern(13,1,1)=13; %ID
pattern(13,3,1)=14; %after #1

%block 14
pattern(14,1,1)=14; %ID
pattern(14,2,1)=13; %before #1
pattern(14,3,1)=5; %after #1

%block 15
pattern(15,1,1)=15; %ID
pattern(15,3,1)=2; %after #1

%block 16
pattern(16,1,1)=16; %ID
pattern(16,3,1)=17; %after #1

%block 17
pattern(17,1,1)=17; %ID
pattern(17,2,1)=16; %before #1
pattern(17,3,1)=2; %after #1

%block 18
pattern(18,1,1)=18; %ID
pattern(18,3,1)=19; %after #1

%block 19
pattern(19,1,1)=19; %ID
pattern(19,2,1)=18; %before #1
pattern(19,3,1)=9; %after #1

%block 20
pattern(20,1,1)=20; %ID
pattern(20,3,1)=4; %after #1

%block 21
pattern(21,1,1)=21; %ID
pattern(21,3,1)=22; %after #1

%block 22
pattern(22,1,1)=22; %ID
pattern(22,2,1)=21; %before #1
pattern(22,3,1)=4; %after #1

%block 23
pattern(23,1,1)=23; %ID
pattern(23,3,1)=7; %after #1

%block 24
pattern(24,1,1)=24; %ID
pattern(24,3,1)=7; %after #1

%block 25
pattern(25,1,1)=25; %ID
pattern(25,2,1)=1; %before #1
pattern(25,3,1)=9; %after #1

%% variables and prompts

%chance that progression will jump green on any given change
jchance=input('Input the percent chance that the progression will jump to a green space.\n');
jchance=jchance/100;

%chance the progression will reverse direction for the next change on any
%given change
rchance=input('Input the percent chance that the progression will go against the arrows.\n');
rchance=rchance/100;

%whether or not the progression will start on im, end on im, or neither
onestart=input('Will your progression START on im? "1" for yes, "0" for no.\n');
oneend=input('Will your progression END on im? "1" for yes, "0" for no.\n');

%whether the progression will ignore if it has already reversed or jumped
ignore=input('Will the progression ignore whether or not it has just jumped or reversed? "1" for yes, "0" for no.\n');

%misc scoreboard
bluestart=1;
blueend=8;
greenstart=10;
greenend=25;

onefound=0;
justjumped=0;
jumping=0;
justreversed=0;
reversing=0;
%% runs the flow

%{
finding the first non-im chord:
uses a random number between 1 and 8 and finds the closest integer to that
in order to choose from only one of the blue boxes
%}
rand1=round(bluestart+((blueend-bluestart)*rand));
j=1;
chordProgressionBox(j)=rand1; %first non-im chord has the value in box 2
j=j+1;


%now onto the part that will continue until im is found
while onefound==0
    possibleMoves=[];
    %decides whether to roll dice for jumping and reversing based on
    %whether or not it has just jumped or reversed, and if we're ignoring
    %that fact
    if (justjumped==0 && justreversed==0) || ignore==1
        %rolls dice of if it is about to reverse direction or jump
        jumproll=rand;
        if jumproll<=jchance
            jumping=1;
        end
        
        revroll=rand;
        if revroll<=rchance
            reversing=1;
        end
        %if both happen to come out successes, tiebreaks them
        if jumping==1 && reversing==1
            tiebreak=rand;
            if tiebreak<=0.5
                jumping=0;
            else
                reversing=0;
            end
            
        end
    end
    
    if jumping==1
        %finds random number within green values
        rand2=round(greenstart+((greenend-greenstart)*rand));
        
        %and uses that as the next chord
        chordProgressionBox(j)=rand2;
        
        %setting scoreboard
        justjumped=1;
        jumping=0;
        justreversed=0;
    elseif reversing==1
        %finds all boxes coming from last chosen chord that are against the
        %flow
        k=1;
        for i=1:6
            if pattern(chordProgressionBox(j-1),2,i)~=0
                possibleMoves(k)=pattern(chordProgressionBox(j-1),2,i);
                k=k+1;
            end
        end
        movecountpre=size(possibleMoves);
        movecount=movecountpre(2);
        if movecount==0 %if there are no possible moves (green box with no ante)
             k=1; 
             for i=1:6
                if pattern(chordProgressionBox(j-1),3,i)~=0
                    possibleMoves(k)=pattern(chordProgressionBox(j-1),2,i);
                    k=k+1;
                end
             end
        end
        movecountpre=size(possibleMoves);
        movecount=movecountpre(2);
        
        %finds random number within amount of move choices
        rand3=round(1+((movecount-1)*rand));
        
        %and uses that as the next chord
        chordProgressionBox(j)=possibleMoves(rand3);
        
        %setting scoreboard
        justjumped=0;
        justreversed=1;
        reversing=0;
    else %if we're not reversing or jumping
        %finds all boxes coming from last chosen chord that are with the
        %flow
        k=1;
        for i=1:6
            if pattern(chordProgressionBox(j-1),3,i)~=0
                possibleMoves(k)=pattern(chordProgressionBox(j-1),3,i);
                k=k+1;
            end
        end
        movecountpre=size(possibleMoves);
        movecount=movecountpre(2);
        
        %finds random number within amount of move choices
        rand4=round(1+((movecount-1)*rand));
        
        %and, unless we've reached im, uses that as the next chord
        if movecount==0
            onefound=1;
            
        else
            chordProgressionBox(j)=possibleMoves(rand4);
            
        end
        
        %setting scoreboard
        justjumped=0;
        justreversed=0;
    end
    
    j=j+1;
    
end

%% final cuts and additions
%adds im on to the beginning or end
if onestart==1 && oneend==1
    chordBoxFinal=[9 chordProgressionBox 9];
elseif onestart==1
    chordBoxFinal=[9 chordProgressionBox];
elseif oneend==1
    chordBoxFinal=[chordProgressionBox 9];
end
