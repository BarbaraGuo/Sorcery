CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
OBJECTS = airElemental.o apprenticeSummoner.o auraOfPower.o banish.o blizzard.o board.o boneGolem.o card.o darkRitual.o deck.o disenchant.o earthElemental.o enchantment.o enrage.o fireElemental.o giantStrength.o haste.o magicFatigue.o main.o masterSummoner.o minion.o novicePyromancer.o player.o potionSeller.o raiseDead.o recharge.o ritual.o silence.o spell.o standstill.o unsummon.o model.o controller.o view.o graphicsView.o textView.o ascii_graphics.o window.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = sorcery

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/usr/X11R6/lib -lX11
-include ${DEPENDS}

.PHONY:clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS} 
	
