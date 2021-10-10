library ieee;
use ieee.std_logic_1164.all;

-- 1,2,0,3,1 promjene stanja
-- res vraca direktno u 1

entity moore is
    port (
        res, clk : in std_logic;
        y : out std_logic_vector(1 downto 0);
    );
end moore;

architecture moore_beh is
    type state is (NULA, JEDAN, DVA, TRI);
    signal cur_state : state := JEDAN;
    signal next_state : state;
    begin
        transfer : process(res,  clk)
            begin
                if (res = '1') then
                    cur_state <= JEDAN;
                elsif (clk'event and clk = '1') then
                    if (cur_state = JEDAN) then
                        next_state = DVA;
                    elsif (cur_state = DVA) then
                        next_state = NULA;
                    elsif (cur_state = NULA) then
                        next_state = TRI;
                    elsif (cur_state = TRI) then
                        next_state = JEDAN;
                    end if;
                end if;
            end process;
        clock_process : process(clk)
                            begin
                                if (rising_edge(clk)) then
                                    cur_state <= next_state;
                                end if;
                        end process;
        final_process : process(cur_state)
                                    begin
                                        if (cur_state = JEDAN) then y <= "01";
                                        elsif (cur_state = DVA) then y <= "10";
                                        elsif (cur_state = TRI) then y <= "11";
                                        elsif (cur_state = NULA) then y <= "00";
                                        end if;
                        end process;
end moore_beh;
