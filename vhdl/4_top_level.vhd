library ieee;

entity top_level is
    port (
        in1, in2 : in std_logic;
        clk : in std_logic;
        out_level : out std_logic;
    );
end top_level;

entity and_sklop is
    port (
        x,y : in std_logic;
        z : out std_logic;
    );
end and_sklop;

architecture and_behavioral of and_sklop is
    begin
        z <= '1' when x = '1' and y = '1' else '0';
end and_behavioral;

entity or_sklop is
    port (
        x,y : in std_logic;
        z : out std_logic;
    );
end or_sklop;

architecture or_behavioral of or_sklop is
    begin
        z <= '1' when x = '1' or y = '1' else '0';
end or_behavioral;

architecture top_level_behavioral of top_level is
    component and_comp
        port (
            x,y : in std_logic;
            z : out std_logic;
        );
    end component;

    component or_comp
        port (
            x,y : in std_logic;
            z : out std_logic;
        );
    end component;

    signal and_out, or1_out or2_out : std_logic;
    begin
        and_s : and_comp port map (x => in1, y => in2, z => and_out);
        or1_s : and_comp port map (x => in1, y => in2, z => or1_out);
        or2_s : and_comp port map (x => and_out, y => or1_out, z => or2_out);
        
        process (clk)
            begin
                if (clk'event and clk = '1') then
                    z <= or2_out;
                end if;
        end process;
end top_level_behavioral;