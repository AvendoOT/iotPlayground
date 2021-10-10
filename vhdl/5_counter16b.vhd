library ieee;
use ieee.std_logic_1164.all;

entity counter16b is
    port(
        cnt_input: in std_logic_vector(3 downto 0);
        up_down: in std_logic; -- 1 inkrement, 0 dekrement
        enable: in std_logic; -- count if 1
        reset: in std_logic;
        cnt: out std_logic_vector(15 downto 0);
    );
end counter16b;

architecture counter_behavioral of counter16b is
    signal counter : std_logic_vector (15 downto 0);
    signal value : std_logic_vector (3 downto 0) := cnt_input;

    begin
        process(clk, reset, enable, up_down)
            begin
                if (reset = '1') then
                    counter <= '0000000000000000';
                end if;
                if (clk'event and clk = '1') then
                    if (enable = '1') then
                        if (up_down = '1') then
                            counter <= counter + value;
                        elsif (up_down = '0') then
                            counter <= counter - value;
                        end if;
                    end if;
                end if;
        end process;
        cnt <= counter;
end counter_behavioral;