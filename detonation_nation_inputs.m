%% Initialize input structures with default values for RDRE Blowdown Model
% OPTS: structure containing model options.
% GBL: structure containing global variables.
%
% Michael Cooper (michael.cooper-1@nasa.gov)

function [opts, gbl] = detonation_nation_inputs(pressure, temperature, ofr)
% our team name is "detonation nation"
% treat inputs as vectors

%% Options
opts = struct;
%NOTE: need to change fuel to RP-1 and oxidizer to air



% Propellants - Used by CEA to determine mixture properties pre- and post-detonation.
% Can either define this as a single component, or a mixture by mass
% fraction e.g. {'RP-1',0.25,'CH4',0.75} is 25% RP-1 and 75% CH4.
opts.Fuel = 'RP-1'; % The fuel used by the RDRE
opts.Oxid = 'Air'; % The oxidizer used by the RDRE

% Components to omit from low-temperature CEA calculations (TP problems).
% By default this is pure carbon and condensed water.
% No species are omitted from combustion calculations (HP, UV, RKT problems)
opts.FuelOmit = {'C(gr)','H2O(cr)','H2O(L)'};
opts.OxidOmit = {'C(gr)','H2O(cr)','H2O(L)'};

% This choice determines if plottable data is saved during the sim and
% output as "cycle_data". It increases runtime, so you can turn this off if 
% you don't need it.
opts.PlotFlag = 0; % Flag for outputting cycle_data.

opts.Summer = 0 ;  % This logic flag determines whether the Summerfield approximation for 
                    % separated flow in overexpanded nozzles is applied. If set to 0, the pressure ratio at which separation occurs is set to 0.0002 
                    % (very small).  If set to 1, then Summerfield's value of 0.37 is used.
opts.Frozen = 0;    % Flag for frozen composition in nozzle flow.

% Vacuum: Set this to 1 if you are simulating vacuum operation. gbl.P_amb
% will automatically be set to match the nozzle exit pressure.
opts.Vacuum = 0;

% Maximum iterations that will be performed by BDOWN_Loop in search of limit
% cycle, and max iterations that will be performed when finding gamma.
opts.MaxIter = 100;

% CEA options - if these are set to 1, they are auto-calculated by the program
opts.AutocalcGamma = 1; % If set to zero, user must define gbl.gam
opts.AutocalcGasConstant = 1; % If set to zero, user must define gbl.R_g
opts.AutocalcCombustionHeat = 1; % If set to zero, user must define gbl.h_c

% Option for auto-calculating the heat transfer parameter beta.
opts.AutocalcBeta = 1; % If set to zero, user must define gbl.beta


%% Globals
gbl = struct;

gbl.dti = 0.001;   % Numerical integration time step, non-dimensionalized by the wave tranit time L/a*

% Engine geometry
gbl.arn = 22;       % Ratio of exit area to throat area
gbl.art = 0.8;      % Ratio of throat area to tube area. For the RDRE simulation, this should not 
                    % be changed. It controls the fill Mach number and was chosen to match what
                    % is typically found in high fidelity RDRE simulations
gbl.D_mean = 11.8;  % Mean diameter, in
gbl.ht = 0.80;      % This is the inner body to outer body diameter ratio. The current value has 
                    % no special meaning. We do not yet know the limits. hub-to-tip ratio.
gbl.AR = 5;    % Engine aspect ratio, ratio of length to annulus hydraulic diameter

% RDRE operating characteristics
gbl.P_in = pressure;    % CHANGED. Pressure delivered to combustion chamber by injectors, psia

gbl.P_amb = 3.458;   % Ambient pressure, psia
gbl.T_in = temperature;     % CHANGED. Temperature of mixture delivered to combustion chamber, R
gbl.T_wall = 2400;  % Assumed wall temperature to which hot gas heat is transferred, R

% Heat transfer
gbl.Pr = 0.7;       % Prandtl number, if set to 0, heat transfer calculation is turned off

% Combustion model
gbl.OFR = ofr;     %CHANGED. O/F ratio
gbl.eta_c = 1.0;   % Combustion efficiency
gbl.eta_d = 0.0;      % Fraction of heat release consumed by parasitic deflagration


end